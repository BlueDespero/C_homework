#include <stdio.h>
#include <math.h>

//Maria Szlasa 313990
//wyznaczanie liczby narcystycznej najblizszej podajnej liczbie n  w systemie o bazie b

unsigned long long int zmiana_systemu(int base, unsigned long long int n)
{
    unsigned long long int liczba=0, mnoznik=1;
    while(n!=0)
    {
        liczba+=mnoznik*(n-n/base*base);
        n/=base;
        mnoznik*=10;
    }
    return liczba;
}

int main()
{
    unsigned long long int n, base, liczba;
    scanf("%llu %llu",&n,&base);

    while(1)
    {
        liczba=zmiana_systemu(base,n);
        int dlugosc=0;
        unsigned long int liczba_p=liczba, kandydat=0;
        while(liczba_p!=0)
        {
            liczba_p/=10;
            dlugosc++;
        }
        liczba_p=liczba;
        while(liczba_p!=0)
        {
            kandydat+=pow(liczba_p%10,dlugosc);
            liczba_p/=10;
        }
        if(kandydat==n)
        {
            printf("%llu %llu %llu", base, n, liczba); //Tu były złe typy zmiennych
            return 0;
        }
        n++;
    }
}
