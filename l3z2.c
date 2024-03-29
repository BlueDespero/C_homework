#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char text_tape[10000];
char command_tape[10000];
char storage[10000];
int pointer = 0;
int max_length = 0;

int type;
int arg_a;
int arg_b;
char arg_string[10000];


void find_type(int curr)
{
    if(command_tape[curr+2] == 'U')
        type = 0;
    if(command_tape[curr+2] == 'O')
        type = 1;
    if(command_tape[curr+2] == 'A')
        type = 2;
    if(command_tape[curr+2] == 'N')
        type = 3;
}

void find_arguments(int curr_pointer)
{
    //Cut case
    if (type == 0)
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
        arg_a = strtol(argument, &pEnd, 10);


        curr_pointer = end;
        while (command_tape[curr_pointer]==' ')
            curr_pointer+=1;


        begin = curr_pointer;
        end = curr_pointer;
        while (command_tape[end]!=' ' && command_tape[end]!='$' && end < max_length)
            end+=1;
        strncpy(argument,command_tape+begin, end-begin);
        arg_b = strtol(argument, &pEnd, 10);
        curr_pointer = end;
        //printf("\n%d  %d\n", arg_a, arg_b);
    }

    //Copy case
    if (type == 1)
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
        arg_a = strtol(argument, &pEnd, 10);


        curr_pointer = end;
        while (command_tape[curr_pointer]==' ')
            curr_pointer+=1;


        begin = curr_pointer;
        end = curr_pointer;
        while (command_tape[end]!=' ' && command_tape[end]!='$' && end<max_length)
            end+=1;
        strncpy(argument,command_tape+begin, end-begin);
        arg_b = strtol(argument, &pEnd, 10);
        curr_pointer = end;
    }

    //Paste case
    if (type == 2)
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
        arg_a = strtol(argument, &pEnd, 10);
        curr_pointer = end;
    }

    //Insert case
    if (type == 3)
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
        arg_a = strtol(argument, &pEnd, 10);


        curr_pointer = end;
        while (command_tape[curr_pointer]==' ')
            curr_pointer+=1;


        begin = curr_pointer;
        end = curr_pointer;
        while (command_tape[end]!=' ' && command_tape[end]!='$' && end<max_length) 
            end+=1;
        strncpy(arg_string,command_tape+begin, end-begin);
        curr_pointer = end;
    }
    pointer = curr_pointer;
}

void execute_command()
{
    //Cut case
    if (type == 0)
    {
        for (int i = 0; i < arg_b; i++)
            storage[i] = text_tape[i+arg_a];

        char new_text[10000];
        for (int i = 0; i < arg_a; i++)
            new_text[i] = text_tape[i];


        for (unsigned int i = arg_a; i < (strlen(text_tape)-arg_b); i++)
            new_text[i] = text_tape[i+arg_b];

        strncpy(text_tape, new_text,strlen(new_text));
        for (unsigned int i = strlen(text_tape) - arg_b; i < strlen(text_tape); i++)
            text_tape[i] = '\0';
    }

    //Copy case
    if (type == 1)
        strncpy(storage, text_tape + arg_a, arg_b);

    //Paste case
    if (type == 2)
    {
        char new_text[10000];
        strncpy(new_text+arg_a+strlen(storage), text_tape+arg_a, strlen(text_tape) - arg_a);
        strncpy(new_text+arg_a, storage, strlen(storage));
        strncpy(new_text, text_tape, arg_a);
        strncpy(text_tape, new_text, strlen(new_text));
    }

    //Insert case
    if (type == 3)
    {
        char new_text[10000];
        for (int i = 0; i < arg_a; i++)
            new_text[i] = text_tape[i];

        for (unsigned int i = 0;i<strlen(arg_string);i++)
            new_text[i+arg_a] = arg_string[i];

        for (unsigned int i = (arg_a+strlen(arg_string)); i < strlen(text_tape); i++)
            new_text[i] = text_tape[i-strlen(arg_string)];

        strncpy(text_tape, new_text, strlen(new_text));
    }
}

void read_command(void)
{
    int temp = pointer;
    
    while (command_tape[temp]!='$')
        temp+=1;

    find_type(temp);
    find_arguments(temp);
}

int main(void)
{
    fgets(text_tape,10000,stdin);
    fgets(command_tape,10000,stdin);
    max_length = strlen(command_tape);

    while (pointer<max_length)
    {
        read_command();
        execute_command();
    }
    printf("%s",text_tape);
    return 0;
}