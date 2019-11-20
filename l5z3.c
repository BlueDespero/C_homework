#include<stdio.h>

//---------------------------------------------------------------------------------

struct signature_part
{
    int place;
    char x_or_y;
};

struct negation_rule
{
    int condition_state;
    char condition_x_y;
    int condition_byte;

    char to_negate_x_y;
    int to_negate_byte;
};

struct scraping_result
{
    struct signature_part signature[32];
    int signature_len;
    struct negation_rule rules_of_negation[64];
    int n_len;
};

struct coords
{
    long long x;
    long long y;
};

struct dir_entry
{
    char key1;
    int key2;
    int value;
};

struct dir
{
    struct dir_entry entries[1024];
    int dir_len;
};

//---------------------------------------------------------------------------------

int char_to_dec(char t)
{
    if (t < 58)
        return t-48;
    return t-55;
}

struct scraping_result scrap_signature_and_rules(char provided[1024])
{
    struct scraping_result result;
    int end = 1;
    result.signature_len = 0;
    result.n_len = 0;

    while (provided[end] != ']')
    {
        end++;
        while (provided[end] != ' ' && provided[end] != ']') end++;
        
        struct signature_part part;
        part.place = char_to_dec(provided[end-1]);
        part.x_or_y = provided[end-2];

        result.signature[result.signature_len] = part;
        result.signature_len+=1;
    }


    while (provided[end]!='\n')
    {
        end++;
        while (provided[end]!='(' && provided[end]!='\n') end++;

        if (provided[end] != '\n')
        {
            struct negation_rule rule;  
            rule.to_negate_x_y = provided[end+4];
            rule.to_negate_byte = char_to_dec(provided[end+5]);

            rule.condition_x_y = provided[end+7];
            rule.condition_byte = char_to_dec(provided[end+8]);
            rule.condition_state = char_to_dec(provided[end+10]);

            result.rules_of_negation[result.n_len]=rule;
            result.n_len+=1;
        }
    }
    return result;    
}

struct coords scrap_coordinates(char coordinates[64])
{
    struct coords results;
    if(coordinates[1] == 'x')
    {
        long long x=0, y=0;
        int pointer = 7;

        while (coordinates[pointer] != ',')
        {
            x*=10;
            x+=char_to_dec(coordinates[pointer]);
            pointer++;
        }
        pointer++;
        while (coordinates[pointer] != ')')
        {
            y*=10;
            y+=char_to_dec(coordinates[pointer]);
            pointer++;
        }
        results.x = x;
        results.y = y;
    }
    else
    {
        long long x=0, y=0;
        int pointer = 7;

        while (coordinates[pointer] != ',')
        {
            y*=10;
            y+=char_to_dec(coordinates[pointer]);
            pointer++;
        }
        pointer++;
        while (coordinates[pointer] != ')')
        {
            x*=10;
            x+=char_to_dec(coordinates[pointer]);
            pointer++;
        }
        results.x = x;
        results.y = y;
    }
    return results;
}

int get_bit(long long number, int place)
{
    long long c = 1<<place;
    number = number&c;
    if (number == 0)
        return 0;
    return 1;
}

int find_in_dir(struct dir directory, char key1, int key2)
{
    int i = 0;
    while(!(directory.entries[i].key1 == key1 && directory.entries[i].key2 == key2)) i++;
    return directory.entries[i].value;
}

long long implement_negations(long long result, struct scraping_result pack, struct dir directory)
{
    for (int i = 0; i<pack.n_len;i++)
    {
        struct negation_rule rule = pack.rules_of_negation[i];
        int a = find_in_dir(directory, rule.condition_x_y, rule.condition_byte);
        //printf("\n%c%d %d \n",rule.condition_x_y, rule.condition_byte, a);
        if (get_bit(result, a) == pack.rules_of_negation[i].condition_state)
        {
            int b = find_in_dir(directory, pack.rules_of_negation[i].to_negate_x_y, pack.rules_of_negation[i].to_negate_byte);
            result = result^(1<<b);
        }
    }
    return result;
}


long long encode(char provided[1024], char coordinates[64])
{
    long long result = 0;
    struct scraping_result scrapped = scrap_signature_and_rules(provided);
    struct coords scrapped_coords = scrap_coordinates(coordinates);
    struct dir directory;
    directory.dir_len=0;

    for (int i = 0; i<scrapped.signature_len; i++)
    {
        int n = scrapped.signature_len-i-1;
        struct signature_part curr_part = scrapped.signature[i];

        struct dir_entry entry = {curr_part.x_or_y, curr_part.place, n};
        directory.entries[directory.dir_len] = entry;
        directory.dir_len+=1;

        int b;

        if (curr_part.x_or_y == 'x')
            b = get_bit(scrapped_coords.x, curr_part.place);
        else
            b = get_bit(scrapped_coords.y, curr_part.place);
        result += b<<n;
    }

    result = implement_negations(result, scrapped, directory);
    return result;
}

long long execute_rule(long long value, int iter, int n_len, struct negation_rule rules[64], int used_rules[64], struct dir directory)
{
    used_rules[iter] = 1;

    for (int i = 0; i < n_len; i++)
        if (rules[iter].condition_x_y == rules[i].to_negate_x_y && rules[iter].condition_byte == rules[iter].to_negate_byte)
            value = execute_rule(value, i, n_len, rules, used_rules, directory);

    int condition_place = find_in_dir(directory, rules[iter].condition_x_y, rules[iter].condition_byte);
    int negate_place = find_in_dir(directory, rules[iter].to_negate_x_y, rules[iter].to_negate_byte);

    if (rules[iter].condition_state == get_bit(value, condition_place))
        value = value^(1<<negate_place);

    return value;
}

long long negate_negations(long long value, struct negation_rule rules[64], int n_len, struct dir directory)
{
    int used_rules[64] = {0};

    for (int i = 0; i < n_len; i++)
        if (used_rules[i] == 0)
            value = execute_rule(value, i, n_len, rules, used_rules, directory);

    return value;
}

void decode(char provided[1024], long long value)
{
    struct scraping_result scrapped = scrap_signature_and_rules(provided);

    long long x = 0;
    long long y = 0;

    struct dir directory;
    directory.dir_len=0;

    for (int i = 0; i<scrapped.signature_len; i++)
    {
        int n = scrapped.signature_len-i-1;
        struct signature_part curr_part = scrapped.signature[i];

        struct dir_entry entry = {curr_part.x_or_y, curr_part.place, n};
        directory.entries[directory.dir_len] = entry;
        directory.dir_len+=1;
    }

    value = negate_negations(value, scrapped.rules_of_negation, scrapped.n_len, directory);

    for (int i = 0; i < scrapped.signature_len; i++)
    {
        int n = scrapped.signature_len - i - 1, b = get_bit(value,n);
        if (b==0)
            continue;
        struct signature_part curr_part = scrapped.signature[i];

        if (curr_part.x_or_y == 'x')
            x+=b<<curr_part.place;
        else
            y+=b<<curr_part.place;
    }
    printf("(y,x)=(%lld,%lld)",y,x);
}

int main()
{
    char mode[16], provided[1024], coordinates[64];

    fgets(mode,16,stdin);
    fgets(provided,1024,stdin);

    if (mode[0] == 'e')
    {
        fgets(coordinates,64,stdin);
        printf("%lld",encode(provided, coordinates));        
    }
    else
    {
        long long value;
        scanf("%lld", &value);
        decode(provided, value);
    }

    return 0;
}