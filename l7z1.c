#include<stdio.h>
#include<stdbool.h>
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

void inicjuj_slownik(struct slownik *s)
{
    s->ile_par=0;
}

bool znajdz_pozycje(struct slownik *s, int klucz, unsigned *pozycja)
{
    for (unsigned i = 0; i < s->ile_par; i++)
        if (s->tbl[i].klucz == klucz)
        {
            *pozycja=i;
            return 1;
        }
    return 0;
}

char* znajdz(struct slownik *s, int klucz)
{
    for (unsigned i = 0; i < s->ile_par; i++)
        if (s->tbl[i].klucz == klucz)
            return s->tbl[i].wartosc;
    return NULL;
}

bool wstaw(struct slownik *s, int klucz, char *wartosc)
{
    if (znajdz(s, klucz) == NULL)
    {
        struct para nowa_para = {klucz, wartosc};
        s ->tbl[s->ile_par] = nowa_para;
        s->ile_par++;
        return 1;
    }
    return 0;
}

void wypisz(struct slownik *s)
{
    for (unsigned i = 0; i < s->ile_par; i++)
        printf("%d:  %s\n", s->tbl[i].klucz, s->tbl[i].wartosc);
}


int main() {
    struct slownik s;
    struct slownik *wsk_s = &s;
    inicjuj_slownik(wsk_s);

    unsigned pozycja;
    unsigned *p = &pozycja;

    assert(s.ile_par == 0);
    assert(znajdz(wsk_s, 1) == NULL);

    assert(znajdz_pozycje(wsk_s, 1, p) == 0);
    wstaw(wsk_s,1,"A");
    assert(znajdz_pozycje(wsk_s,1,p) == 1);
    assert(pozycja == 0);
    wypisz(wsk_s);

    char* cel1 = "A";
    assert(znajdz(wsk_s,1) == cel1);
    assert(znajdz(wsk_s,2) == NULL);

    wstaw(wsk_s,3,"B");
    wstaw(wsk_s,5,"c");
    printf("\n");
    wypisz(wsk_s);

    assert(wstaw(wsk_s,3,znajdz(wsk_s,3)) == 0);
    assert(wstaw(wsk_s,2,znajdz(wsk_s,3)) == 1);
    assert(wstaw(wsk_s,4,znajdz(wsk_s,3)) == 1);
    printf("\n");
    wypisz(wsk_s);

    inicjuj_slownik(wsk_s);
    printf("\n");
    wypisz(wsk_s);
    assert(wstaw(wsk_s,3,"c") == 1);
    assert(wstaw(wsk_s,2,znajdz(wsk_s,3)) == 1);
    assert(wstaw(wsk_s,4,znajdz(wsk_s,3)) == 1);
    printf("\n");
    wypisz(wsk_s);
    return 0;
}