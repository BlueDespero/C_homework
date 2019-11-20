#include<stdio.h>
#include <stdbool.h> 

bool czyRzadkieKolejne(unsigned char c1, unsigned char c2);

bool czyRzadki(unsigned char c){
    return (( (c&170) == c) || ( (c&85) == c));}

bool czyRzadkaTab(unsigned char tab[], unsigned rozmiar_tab)
{
    // Aby tablica była rzadka każdy jej element musi być rzadki oraz dwa kolejne elementy nie mogą mieć tej samej wartości na odpowiednio najwcześniejszym i najpóźniejszym bicie.
    bool flag = 1;
    for (unsigned i = 0; i < rozmiar_tab; i++)
        if (!czyRzadki(tab[i]))
            flag = 0;
    
    for (unsigned i = 0; i < rozmiar_tab-1; i++)
        if(!czyRzadkieKolejne(tab[i], tab[i+1]))
            flag = 0;

    return flag;
}

// Najwcześniejszy bit jest zapalony gdy zapisana liczba jest nieparzysta. Najpóźniejszy bit jest zapalony gdy liczba jest >= 128
bool czyRzadkieKolejne(unsigned char c1, unsigned char c2){
    return ( (c1%2) != (c2<128) );}

int main() {

    unsigned char tab[] = {10, 2};
    unsigned rozmiar_tab = sizeof(tab)/sizeof(tab[0]);


    if(czyRzadkaTab(tab, rozmiar_tab))
        printf("Podana tablica oraz wyszstkie jej elementy są rzadkie.\n");
    else
    {
        printf("Podana tablica nie jest rzadka.\n\n");
        for (unsigned i = 0; i < rozmiar_tab; i++)
        {
            if (czyRzadki(tab[i]))
                printf("%d element tablicy jest rzadki\n", i);
            else
                printf("%d element tablicy nie jest rzadki\n", i);
        }
    }
    
    return 0;
}