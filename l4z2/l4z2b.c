// Program wczyta z wejścia liczbę N, dwa ciągi bajtów o rozmiarach odpowiednio N i N/8 bajtów i sprawdzi, czy drugi ciąg jest spakowanym ciągiem bitów parzystości dla pierwszego.
#include "l4z2.h"

int main()
{
    int N;
    int parity_array[10005], proposed_array[10005], generated_array[10005];


    printf("Ile znaków zawiera pierwszy ciąg? (Program pomija spacje i \\n. Drugi ciąg ma długość top(N/8))\n");
    scanf("%d",&N);
    int n = N/8;
    if (N%8 != 0) n++;


    printf("Podaj pierwszy ciąg: \n");
    for (int i = 0; i < N; i++)
    {
        char p;
        do
        {
            p = getchar();
        } while (p == ' ' || p == '\n');
                
        parity_array[i] = count_bits(p)%2;        
    }
    for (int i = 0;i<n;i++)
        generated_array[i] = pack_bytes(parity_array, i*8, i*8+8);


    printf("Podaj drugi ciąg: \n");
    for (int i = 0; i < n; i++)
        scanf("%d", &proposed_array[i]);       


    int flag = 0;
    for (int i = 0; i < n; i++)
        if (generated_array[i] != proposed_array[i])
            flag = 1;


    if (flag == 0)
        printf("\nDrugi ciąg jest spakowanym ciągiem bitów parzystości dla pierwszego.\n");
    else
        printf("\nDrugi ciąg nie jest spakowanym ciągiem bitów parzystości dla pierwszego.\n");
    return 0;
}
