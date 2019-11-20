#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include<assert.h>

bool czyDrzewo(int *drzewo, int w, int n)
{
    int lewe = 2*w+1, prawe = 2*w+1;
    if (w>n)
        return 0;
    if (drzewo[w] == -1)
        return 1;
    return czyDrzewo(drzewo,lewe,n)&czyDrzewo(drzewo,prawe,n);
}

unsigned wysokosc(int *drzewo, int w)
{
    int lewe = 2*w+1, prawe = 2*w+2;
    if (drzewo[w] == -1)
        return 0;

    if (wysokosc(drzewo,lewe) > wysokosc(drzewo,prawe))
        return wysokosc(drzewo,lewe)+1;
    return wysokosc(drzewo,prawe)+1;
}

unsigned czySingleton(int *drzewo, int w){
    return (drzewo[2*w+1] == -1 && drzewo[2*w+2] == -1);}

unsigned ileSingletonow(int *drzewo, int w)
{
    int lewe = 2*w+1, prawe = 2*w+2;
    if (drzewo[w] == -1)
        return 0;
    if (drzewo[lewe] == -1 && drzewo[prawe] == -1)
        return 1;
    return ileSingletonow(drzewo,lewe) + ileSingletonow(drzewo,prawe);
}

unsigned zliczElementy(int *drzewo, int w)
{
    int lewe = 2*w+1, prawe = 2*w+2;
    if (drzewo[w] == -1)
        return 1;
    return zliczElementy(drzewo,lewe) + zliczElementy(drzewo,prawe) + 1;
}

bool czyBalans(int *drzewo, int w)
{
    int lewe = 2*w+1, prawe = 2*w+2;
    if (abs(zliczElementy(drzewo,lewe) - zliczElementy(drzewo,prawe)) <2)
        return 1;
    return 0;
}

int main()
{
 
    int n;
    int s = 2;
    int s1 = 1;
    int drzewo[1000];
    printf("Podaj największy indeks węzła w tablicy: \n");
    scanf("%d", &n);
    n++;

    printf("Podaj wartości w %d węzłach: \n",n);
    for (int i = 0; i < n; i++)
        scanf("%d", &drzewo[i]);

    printf("\nCzy podana tablica jest drzewem?:  %d\n", czyDrzewo(drzewo,0,n));
    printf("Wysokość drzewa zakorzenionego w węźle %d to:  %u\n", s, wysokosc(drzewo,s));
    printf("Czy węzeł %d jest singletonem?: %d\n", s1, czySingleton(drzewo,s1));
    printf("Drzewo zakorzenione w węźle %d zawiera %u singletonów.\n",s, ileSingletonow(drzewo,s));
    printf("Czy drzewo zakorzenione w węźle %d jest zbalansowane?: %d\n",s, czyBalans(drzewo,s));

 
/*    
    int przyklad[] = {7, 6, 7, -1, -1, -1, 43, 0, 0, 0, 0, 0, 0, -1, -1};
    int prz_rozm = sizeof(przyklad) / sizeof(int);


    assert(czyDrzewo(przyklad,0,prz_rozm) == 1);
*/


    return 0;
}
