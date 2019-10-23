#include <stdio.h>


int main(void)
{
    int n;
    double x, eps;
    double xpow = 1.0, nsil = 1.0, count = 0.0, suma = 0.0;
    printf("Podaj liczbę x oraz porządane przybliżenie funkcji: \n");
    scanf("%lf %lf", &x, &eps);
    double addon;

     do
     {

        addon = (xpow)/nsil;
        suma+=addon;

        xpow*=x;
        count+=1;
        nsil*=count;

     }while (eps/10 < addon);

     printf("Wynik = %lf\n", suma);

    return 0;
}
