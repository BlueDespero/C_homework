#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

#define N 500

struct para
{
    int klucz;
    char *wartosc;
};

struct slownik
{
    struct para tbl[N];
    unsigned ile_par;
};

typedef struct slownik slownik;

void inicjuj_slownik(slownik *s)
{
    s->ile_par=0;
}

bool znajdz_pozycje(slownik *s, int klucz, unsigned *pozycja)
{
    for (unsigned i = 0; i < s->ile_par; i++)
        if (s->tbl[i].klucz == klucz)
        {
            *pozycja=i;
            return 1;
        }
    return 0;
}

char* znajdz(slownik *s, int klucz)
{
    for (unsigned i = 0; i < s->ile_par; i++)
        if (s->tbl[i].klucz == klucz)
            return s->tbl[i].wartosc;
    return NULL;
}

bool wstaw(slownik *s, int klucz, char *wartosc)
{
    if (znajdz(s, klucz) == NULL)
    {
        struct para nowa_para = {klucz, wartosc};
        s->tbl[s->ile_par] = nowa_para;
        s->ile_par++;
        return 1;
    }
    return 0;
}

void wypisz(slownik *s)
{
    for (unsigned i = 0; i < s->ile_par; i++)
        printf("%d:  %s\n", s->tbl[i].klucz, s->tbl[i].wartosc);
}

void usun_z_pozycji(slownik *s, unsigned pozycja)
{

    if(pozycja < s->ile_par)
    {
        for (unsigned i = pozycja; i < s->ile_par-1; i++)
        {
            struct para temp = s->tbl[i+1];
            s->tbl[i] = temp;
        }
        s->ile_par--;
    }
}

void usun(slownik *s, int klucz)
{
    unsigned pozycja;
    unsigned *p = &pozycja;

    if (znajdz_pozycje(s, klucz, p) != 0)
        usun_z_pozycji(s, pozycja);
}

bool czy_parzyste(int n){
    return n%2 == 0;}

bool czy_nieparzyste(int n){
    return n%2 == 1;}

void usun_pred(slownik *s, bool (*predykat)(int))
{
    unsigned poczatkowa_dlugosc = s->ile_par;
    unsigned l_usun = 0;
    for (unsigned i = 0; i < poczatkowa_dlugosc; i++)
    {
        if (predykat(s->tbl[i-l_usun].klucz) == 1)
        {
            usun(s, s->tbl[i-l_usun].klucz);
            l_usun++;
        }       
    }

}

int main() {
    slownik *wsk_s = malloc(sizeof(slownik));

    //Polecenie stworzenia funkcji wypisującej zawartość słownika zasugerowała mi, że testowanie powinno odbyć się w 
    //sposób wykonany poniżej zamiast korzystania z funkcji assert. 

    inicjuj_slownik(wsk_s);

    //Testowanie działania funkcji na pustym słowniku
    usun_z_pozycji(wsk_s, 100); 
    usun(wsk_s, 100);
    wypisz(wsk_s);

    printf("--  Wstawienie zawartości do słownika --\n");
    wstaw(wsk_s, 0, "A");
    wstaw(wsk_s, 1, "A");
    wstaw(wsk_s, 3, "B");
    wstaw(wsk_s, 4, "b");
    wypisz(wsk_s);

    printf("\n--  Usunięcie pierwszego indeksu --\n");
    usun(wsk_s, 1);
    printf("\n");
    wypisz(wsk_s);

    printf("\n--  Ponowne usuniecie pierwszego indeksu. Po wcześniejszym usunięcu nastąpiło przenumerowanie --\n");
    usun_z_pozycji(wsk_s, 1);
    printf("\n");
    wypisz(wsk_s);

    printf("\n--  Próba usuniecia nieistniejacego indeksu  --\n");
    usun_z_pozycji(wsk_s, 100);
    usun(wsk_s, 100);
    printf("\n");
    wypisz(wsk_s);

    printf("\n--  Stworzenie nowego słownika  --\n");
    inicjuj_slownik(wsk_s);
    wstaw(wsk_s, 0, "a");
    wstaw(wsk_s, 1, "B");
    wstaw(wsk_s, 2, "C");
    wstaw(wsk_s, 3, "d");
    wstaw(wsk_s, 4, "e");
    wstaw(wsk_s, 5, "F");
    wstaw(wsk_s, 6, "G");
    wstaw(wsk_s, 7, "3");
    printf("\n");
    wypisz(wsk_s);

    printf("\n--  Usuniecie elementów o parzystych kluczach  --\n");
    usun_pred(wsk_s, czy_parzyste);
    printf("\n");
    wypisz(wsk_s);

    printf("\n--  Usuniecie elementów o nieparzystych kluczach  --\n");
    usun_pred(wsk_s, czy_nieparzyste);
    printf("\n");
    wypisz(wsk_s);

    free(wsk_s);
    return 0;
}