// Program wczyta z wejścia liczbę N oraz ciąg N bajtów i wypisze na wyjściu spakowany ciąg jego bitów parzystości.
#include "l4z2.h"

int main()
{
    int N;
    int parity_array[10005];

    printf("Ile znaków zawiera ciąg? (Program pomija spacje i \\n)\n");
    scanf("%d",&N);

    for (int i = 0; i < N; i++)
    {
        char p;
        do
        {
            p = getchar();
        } while (p == ' ' || p == '\n');
                
        parity_array[i] = count_bits(p)%2;        
    }

    int n = N/8;
    if (N%8 != 0) n++;

    printf("Ciąg spakowanych bitów to:\n");
    for (int i = 0;i<n;i++)
        printf("%d ",pack_bytes(parity_array, i*8, i*8+8));
    printf("\n");
    return 0;
}