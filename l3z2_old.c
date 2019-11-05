#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char text_tape[10000];
char command_tape[10000];
char storage[10000];
int pointer = 0;
int max_length = 0;

struct command
{
    int type;
    int arg_a;
    int arg_b;
    char arg_string[10000];
};

int find_type(int curr)
{
    if(command_tape[curr+2] == 'U')
        return 0;
    if(command_tape[curr+2] == 'O')
        return 1;
    if(command_tape[curr+2] == 'A')
        return 2;
    if(command_tape[curr+2] == 'N')
        return 3;
    return 5;   
}

void find_arguments(struct command curr_command, int curr_pointer)
{
    //Cut case
    if (curr_command.type == 0)
    {
        curr_pointer+=4;
        while (command_tape[curr_pointer]==' ')
            curr_pointer+=1;


        int begin = curr_pointer;
        int end = curr_pointer;
        while (command_tape[end]!=' ')
            end+=1;
        char argument[10000];
        char * pEnd;
        strncpy(argument,command_tape+begin, end-begin);
        curr_command.arg_a = strtol(argument, &pEnd, 10);


        curr_pointer = end;
        while (command_tape[curr_pointer]==' ')
            curr_pointer+=1;


        begin = curr_pointer;
        end = curr_pointer;
        while (command_tape[end]!=' ' && command_tape[end]!='$' && end < max_length)
            end+=1;
        strncpy(argument,command_tape+begin, end-begin);
        curr_command.arg_b = strtol(argument, &pEnd, 10);
        curr_pointer = end;
        printf("\n%d  %d\n", curr_command.arg_a, curr_command.arg_b);
    }

    //Copy case
    if (curr_command.type == 1)
    {
        curr_pointer+=5;
        while (command_tape[curr_pointer]==' ')
            curr_pointer+=1;


        int begin = curr_pointer;
        int end = curr_pointer;
        while (command_tape[end]!=' ')
            end+=1;
        char argument[10000];
        char * pEnd;
        strncpy(argument,command_tape + begin, end-begin);
        curr_command.arg_a = strtol(argument, &pEnd, 10);


        curr_pointer = end;
        while (command_tape[curr_pointer]==' ')
            curr_pointer+=1;


        begin = curr_pointer;
        end = curr_pointer;
        while (command_tape[end]!=' ' && command_tape[end]!='$' && end<max_length)
            end+=1;
        strncpy(argument,command_tape+begin, end-begin);
        curr_command.arg_b = strtol(argument, &pEnd, 10);
        curr_pointer = end;
    }

    //Paste case
    if (curr_command.type == 2)
    {
        curr_pointer+=6;
        while (command_tape[curr_pointer]==' ')
            curr_pointer+=1;


        char argument[10000];
        char * pEnd;
        int begin = curr_pointer;
        int end = curr_pointer;
        while (command_tape[end]!=' ' && command_tape[end]!='$' && end<max_length)
            end+=1;
        strncpy(argument,command_tape+begin, end-begin);
        curr_command.arg_a = strtol(argument, &pEnd, 10);
        curr_pointer = end;
    }

    //Insert case
    if (curr_command.type == 3)
    {
        curr_pointer+=7;
        while (command_tape[curr_pointer]==' ')
            curr_pointer+=1;


        char argument[10000];
        char * pEnd;
        int begin = curr_pointer;
        int end = curr_pointer;
        while (command_tape[end]!=' ' && command_tape[end]!='$' && end<max_length)
            end+=1;
        strncpy(argument,command_tape+begin, end-begin);
        curr_command.arg_a = strtol(argument, &pEnd, 10);


        curr_pointer = end;
        while (command_tape[curr_pointer]==' ')
            curr_pointer+=1;


        begin = curr_pointer;
        end = curr_pointer;
        while (command_tape[end]!=' ' && command_tape[end]!='$' && end<max_length) 
            end+=1;
        strncpy(curr_command.arg_string,command_tape+begin, end-begin);
        curr_pointer = end;
    }
    pointer = curr_pointer;
}

void execute_command(struct command curr_command)
{
    //Cut case
    if (curr_command.type == 0)
    {
        for (int i = 0; i < curr_command.arg_b; i++)
            storage[i] = text_tape[i+curr_command.arg_a];
        storage[curr_command.arg_b] = '\0';

        printf("\n%d   %d", curr_command.arg_a, curr_command.arg_b);
        //printf("\n%s\n", storage);
        char new_text[10000];
        strncpy(new_text,text_tape, curr_command.arg_a);
        strncpy(new_text+curr_command.arg_a,text_tape+curr_command.arg_a+curr_command.arg_b, strlen(text_tape)-curr_command.arg_a-curr_command.arg_b);
        strcat(new_text, "\0");
        strncpy(text_tape, new_text,strlen(new_text));
        strcat(text_tape,"\0");
    }

    //Copy case
    if (curr_command.type == 1)
    {
        strncpy(storage, text_tape + curr_command.arg_a, curr_command.arg_b);
        strcat(storage,"\0");
    }

    //Paste case
    if (curr_command.type == 2)
    {
        char new_text[10000];
        strncpy(new_text+curr_command.arg_a+strlen(storage), text_tape+curr_command.arg_a, strlen(text_tape) - curr_command.arg_a);
        strncpy(new_text+curr_command.arg_a, storage, strlen(storage));
        strncpy(new_text, text_tape, curr_command.arg_a);
        strncpy(text_tape, new_text, strlen(new_text));
    }

    //Insert case
    if (curr_command.type == 3)
    {
        char new_text[10000];
        strncpy(new_text+curr_command.arg_a+strlen(curr_command.arg_string), text_tape+curr_command.arg_a, strlen(curr_command.arg_string) - curr_command.arg_a);
        strncpy(new_text+curr_command.arg_a, curr_command.arg_string, strlen(curr_command.arg_string));
        strncpy(new_text, text_tape, curr_command.arg_a);
        strncpy(text_tape, new_text, strlen(new_text));
    }
}

struct command read_command(void)
{
    int temp = pointer;
    struct command r_command;
    
    while (command_tape[temp]!='$')
        temp+=1;

    r_command.type = find_type(temp);
    find_arguments(r_command, temp);

    return r_command;
}

int main(void)
{
    fgets(text_tape,10000,stdin);
    fgets(command_tape,10000,stdin);
    max_length = strlen(command_tape);

    while (pointer<max_length)
    {
        struct command next_command = read_command();
        execute_command(next_command);
        //printf("%s\n",text_tape);
    }

    return 0;
}
