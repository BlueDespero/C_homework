#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char alphabet[128] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz ,";
int map[128];
int map_off[128];
int map_off_reverse[128];
char code_table[64][64];
char mode[256];
char key_text[256];
int key_num[256];
char text[256];
int text_num[256];
char output[256];

void encode(void)
{
    for(unsigned long i = 0; i < strlen(text)-1;i++)
    {
        int y = key_num[i];
        int x = map_off_reverse[text_num[i]];
        output[i] = code_table[x][y];
    }
}

void decode(void)
{
    int reverse_key[256];
    for (unsigned int i = 0; i < strlen(text)-1; i++)
    {
        int k = key_num[i];
        reverse_key[i] = (64 - k)%64;
    }
    for(unsigned int i = 0; i < strlen(text)-1;i++)
    {
        int y = reverse_key[i];
        int x = map_off_reverse[text_num[i]];
        output[i] = code_table[x][y];
    }
}

int main(void)
{
    //mapping from letters to idx in normal alphabet
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
        map_off_reverse[j] = i;
        for (int x = 0; x < 64; x++)
        {
            code_table[i][x] = alphabet[(j+x)%64];   
        }
    }

    fgets(key_text,256,stdin);
    fgets(text,256,stdin);
    
    //fixing the key length
    int mod = strlen(key_text)-1;
    for(unsigned long int i = 0;i<strlen(text)-1;i++)
    {
        int s1 = key_text[i%mod];
        int s2 = map[s1];
        key_num[i] = map_off[s2];        
    }

    for(unsigned long int i = 0;i<strlen(text)-1;i++)
    {
        int s = text[i];
        text_num[i] = map[s];        
    }

    if (mode[0] == 'd')
        decode();
    else
        encode();
    
    printf("%s",output);

    return 0;
}
