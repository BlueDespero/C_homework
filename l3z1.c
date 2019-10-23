#include <stdio.h>
#define W_CYKLU 1
#define POZA_CYKLEM 0

int main(void)
{
    int n;
    int result = 0;
    int checker_array[100005];
    int permutation_array[100005];

    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &permutation_array[i]);
        checker_array[i] = POZA_CYKLEM;        
    }

    for (int i = 0; i < n; i++)
    {
        int j = i;
        if (checker_array[j] == POZA_CYKLEM)
        {
            result+=1;
            while (checker_array[j] == POZA_CYKLEM)
            {
                checker_array[j] = W_CYKLU;
                j = permutation_array[j];
            }
        }
    }
    
    printf("%d\n", result);

    return 0;
}
