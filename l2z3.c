#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char alphabet[128] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz ,";
int map[128];
int map_off[128];
char code_table[64][64];
char mode[256];
char key[256];
char text[256];
char output[256];

void encode(void)
{
    for(unsigned int i = 0; i < strlen(key);i++)
    {
        int y1 = key[i];
        int y2 = map[y1];
        int y = map_off[y2];

        int x1 = text[i];
        int x = map[x1];
        output[i] = code_table[x][y];
    }
}

void decode(void)
{
    int reverse_key[256];
    for (unsigned int i = 0; i < strlen(key); i++)
    {
        int k1 = key[i];
        int k2 = map[k1];
        int k3 = map_off[k2];
        reverse_key[i] = alphabet[(64 - k3)%64];
    }
    for(unsigned int i = 0; i < strlen(key);i++)
    {
        int y1 = reverse_key[i];
        int y2 = map[y1];
        //int y = map_off[y2];

        int x1 = text[i];
        int x = map[x1];
        output[i] = code_table[x][y2];
    }
}

int main(void)
{
    for (int i = 0; i < 64; i++)
    {
        int h = alphabet[i];
        map[h] = i;        
    }


    fgets(mode,256,stdin);
    for (int i = 0; i<=64;i++)
    {
        int j;
        scanf("%d",&j);
        map_off[i] = j;
        for (int x = 0; x < 64; x++)
            code_table[i][x] = alphabet[(j+x)%64];
    }

    fgets(key,256,stdin);
    fgets(text,256,stdin);
    
    int mod = strlen(key)-1;
    for(unsigned int i = strlen(key)-1;i<strlen(text)-1;i++)
        key[i] = key[i%mod];
    
    encode();
    printf("\n%s",output);

    /*
    printf("Mode  %s",mode);
    printf("Permutated  %s",permutated_alphabet);
    printf("\nKey  %s",key);
    printf("\nText  %s",text);
    */

    return 0;
}
