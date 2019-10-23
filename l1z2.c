#include <stdio.h>
#include <math.h>

int spr_dane(int a, int b)
{
    if (b<a)
        return 1;
    if (a<0)
        return 1;
    return 0;
}

int czy_kwadrat(double x)
{
    while (x>0.0)
        x-=1.0;
    if (x == 0.0)
        return 1;
    return 0;
}

int main(void)
{
    int a,b;

    printf("Podaj zakres: \n");
    scanf("%d %d",&a, &b);

    if (spr_dane(a,b))
    {
        printf("BLAD");
        return 0;
    }

    int count = 0;

    for(int i = a; i<=b;i++)
    {
        double s = sqrt(i);
        if(czy_kwadrat(s))
            count+=1;
    }

    printf("W podanym zakresie jest %d liczb kwadratowych.", count);

    return 0;
}
