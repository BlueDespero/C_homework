#include <stdio.h>

int wesola(int x)
{
    int spr[100000] = {0};
    int akt = x;
    int suma = 0;

    while (spr[akt]!=1)
    {
        spr[akt] = 1;
        suma = 0;
        while (akt > 0)
        {
            suma=suma + (akt%10)*(akt%10);
            akt = akt/10;
        }
        akt = suma;
    }

    if (akt == 1)
        return 1;
    return 0;
}

int main(void)
{
    int a;
    int z = 0;

    scanf("%d", &a);

    for(int i = a; i<=a+10;i++)
    {
        if (wesola(i))
        {
            z = i;
            break;
        }
    }

    if (z != 0)
        printf("%d",z);
    else
        printf("BRAK");

    return 0;
}