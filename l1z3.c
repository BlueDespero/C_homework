#include <stdio.h>
#include <limits.h>
#include <math.h>

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

int main(void)
{
    unsigned int s;
    int czy = 0;

    scanf("%u",&s);

    for (unsigned int i = s+1; i <= INT_MAX; i++)
    {
        unsigned int a_sum = policz_dzielniki(i);
        if (a_sum>s && a_sum<=INT_MAX)
        {
            unsigned int b_sum = policz_dzielniki(a_sum);
            if (i==b_sum && b_sum!=a_sum)
            {
                printf("%u %u", b_sum, a_sum);
                czy = 1;
                break;                
            }
        }
    }

    if (czy == 0)
        printf("BRAK");
}