#ifndef STDIO_H
#define STDIO_H "stdio.h"
#include <stdio.h>
#endif // !stdio.h

#define L4Z2_H "l4z2"

int count_bits(int number)
{
    int result = 0;
    while (number>0)
    {
        if (number%2)
            result++;
        number/=2;
    }
    return result;
}

int pack_bytes(int *array, int begin, int end)
{
    int result = 0;
    for (int i = begin;i<end;i++)
    {
        result*=2;
        result+=array[i];
    }
    return result;
}

void clear_input()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}