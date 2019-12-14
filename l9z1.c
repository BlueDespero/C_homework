#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define N 10

int main(int argc, char const *argv[])
{
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-") == 0)
        {
            for (int i = 0; i < N; i++)
            {
                char s_char = ' ';
                while (s_char!='\n')
                {
                    s_char = getchar();
                    printf("%c", s_char);
                }               
            }
        }
        else
        {
            FILE *curr_file;
            curr_file = fopen(argv[i], "r");
            printf("\n===> %s <===\n", argv[i]);

            for (int i = 0; i < N; i++)
            {
                char single_char = ' ';
                while (single_char != '\n')
                {
                    fscanf(curr_file,"%c",&single_char);
                    if (!feof(curr_file))
                        printf("%c", single_char);
                    else
                        break;
                }                    
            }
            fclose(curr_file);
        }
    }
    
    
    return 0;
}
