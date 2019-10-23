#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char text_tape[10000];
char command_tape[10000];
int pointer = 0;

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
    if(command_tape[curr+2] == '')
        return 1;
    if(command_tape[curr+2] == 'U')
        return 2;
    if(command_tape[curr+2] == 'U')
        return 3;   
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
        while (command_tape[curr_pointer]!=' ')
            end+=1;
        char argument[10000];
        char * pEnd;
        strncpy(argument,command_tape+begin, begin-end);
        curr_command.arg_a = strtol(argument, &pEnd, 10);


        curr_pointer = end;
        while (command_tape[curr_pointer]==' ')
            curr_pointer+=1;


        begin = curr_pointer;
        end = curr_pointer;
        while (command_tape[curr_pointer]!=' ' && command_tape[curr_pointer]!='$')
            end+=1;
        strncpy(argument,command_tape+begin, begin-end);
        curr_command.arg_b = strtol(argument, &pEnd, 10);
    }

    //Copy case
    if (curr_command.type == 1)
    {
        curr_pointer+=5;
        while (command_tape[curr_pointer]==' ')
            curr_pointer+=1;


        int begin = curr_pointer;
        int end = curr_pointer;
        while (command_tape[curr_pointer]!=' ')
            end+=1;
        char argument[10000];
        char * pEnd;
        strncpy(argument,command_tape+begin, begin-end);
        curr_command.arg_a = strtol(argument, &pEnd, 10);


        curr_pointer = end;
        while (command_tape[curr_pointer]==' ')
            curr_pointer+=1;


        begin = curr_pointer;
        end = curr_pointer;
        while (command_tape[curr_pointer]!=' ' && command_tape[curr_pointer]!='$')
            end+=1;
        strncpy(argument,command_tape+begin, begin-end);
        curr_command.arg_b = strtol(argument, &pEnd, 10);
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
        while (command_tape[curr_pointer]!=' ' && command_tape[curr_pointer]!='$')
            end+=1;
        strncpy(argument,command_tape+begin, begin-end);
        curr_command.arg_a = strtol(argument, &pEnd, 10);
    }

    //Insert case
    if (curr_command.type == 3)
    {
        curr_pointer+=7;
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


    return 0;
}
