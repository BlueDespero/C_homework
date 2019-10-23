#include <stdio.h>
#include <math.h>

#define BIALY '#'
#define CZARNY ' '

int main(void)
{
    int n;
    int czar = 1;

    printf("Podaj liczbę n: ");
    scanf("%d", &n);

    for(int i = 0;i<n*3;i++)
    {
        if(i%3 == 0 && i!=0)
            czar = (czar+1)%2;

        for(int j = 0;j<n*4;j++)
            {
                if(j%4 == 0 && j!=0)
                    czar = (czar+1)%2;

                if (czar==1)
                    putchar(CZARNY);
                else
                    putchar(BIALY);
            }
        printf("\n");
        if (n%2 == 0)
            czar = (czar+1)%2;

    }
}
