#include <stdio.h>
#include <math.h>

int main(void)
{
    int n;
    long long Pell[10005];

    printf("Podaj liczbę n: ");
    scanf("%d", &n);

    Pell[0] = 0;
    Pell[1] = 1;

    for(long long i = 2;i<=n;i++)
        Pell[i] = 2*Pell[i-1] + Pell[i-2];

    for(int i = n;i>=0;i--)
        printf("%lld \n",Pell[i]);
}
