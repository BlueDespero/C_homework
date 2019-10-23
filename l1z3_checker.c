#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>

struct Tuple
{   
    int start;
    unsigned int a;
    unsigned int b;
};


unsigned int policz_dzielniki(int a)
{
    if (a==0)
        return 0;

    unsigned int suma_a = 1;
    for (int i = 2; i <= sqrt(a); i++)
    {
        if (a%i == 0)
        {
            suma_a+=i;
            suma_a+=(a/i);
        }
    }
    return suma_a;
}

struct Tuple zadanie(int s)
{
    unsigned int j = (unsigned int) s;
    for (unsigned int i = j+1; i <= INT_MAX; i++)
    {
        unsigned int a_sum = policz_dzielniki(i);

        if (a_sum>j && a_sum<=INT_MAX)
        {
            unsigned int b_sum = policz_dzielniki(a_sum);
            if (i==b_sum && b_sum!=a_sum)
            {
                struct Tuple r = {s, b_sum, a_sum};
                return r;             
            }
        }
    }

    struct Tuple r = {0,0,0};
    return r;
}

int main(void)
{
    FILE *input_file;
    input_file = fopen("numbers.txt", "r");
    FILE *output_file;
    output_file = fopen("results.txt","w");
    char c[15];
    char *eptr;

    while (fgets(c,15,input_file) != NULL)
    {           
        int d = strtol(c, &eptr,10);
        struct Tuple r = zadanie(d);
        unsigned int start = r.start;
        unsigned int a = r.a;
        unsigned int b = r.b;
        if (a!=0 && b!=0 && start!=0)
            fprintf(output_file,"%u   ||   %u %u\n", start, a, b);
        else
            fprintf(output_file,"%u   ||   BRAK\n", start);
    }
    
    fclose(input_file);
    fclose(output_file);
    return 0;
}