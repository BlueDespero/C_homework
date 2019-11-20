#include <stdio.h>
#include <stdlib.h>


int w, h;


int longest_snake(int board[h][w], int dynamic[h][w])
{
    int best = 1;

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            dynamic[i][j]=1;

            if (i>0 && board[i][j] != board[i-1][j])
            {
                printf("%d  ||  %d\n", board[i][j], board[i-1][j]);
                int curr = dynamic[i-1][j]+1;
                if (curr > dynamic[i][j])
                {
                    dynamic[i][j] = curr;
                    if (curr > best)
                        best = curr;                    
                }
            }


            int c = j;
            while (c>0)
            {
                if (board[i][c-1] != board[i][c])
                {
                    printf("%d  ||  %d\n", board[i][c-1], board[i][c]);
                    if (i>0 && board[i][c-1] != board[i-1][c-1])
                    {
                        int curr = dynamic[i-1][c-1]+1+abs((c-1-j));
                        if (curr > dynamic[i][j])
                            dynamic[i][j] = curr;
                        if (curr > best)
                            best = curr;             
                    }
                    else
                    {
                        int curr = abs((c-1-j)) + 1;
                        if (curr > dynamic[i][j])
                            dynamic[i][j] = curr;
                        if (curr > best)
                            best = curr;             
                    }
                }
                else
                    break;
                c--;
            }


            c = j;
            while (c<w-1)
            {
                if (board[i][c+1] != board[i][c])
                {
                    printf("%d  ||  %d\n", board[i][c+1], board[i][c]);
                    if (i>0 && board[i][c+1] != board[i-1][c+1])
                    {
                        int curr = dynamic[i-1][c+1]+1+abs((c+1-j));
                        if (curr > dynamic[i][j])
                            dynamic[i][j] = curr;
                        if (curr > best)
                            best = curr;
                    }
                    else
                    {
                        int curr = abs((c+1-j)) + 1;
                        if (curr > dynamic[i][j])
                            dynamic[i][j] = curr;
                        if (curr > best)
                            best = curr;
                    }
                }
                else
                    break;
                c++;
            }
        }

    }
    return best;
}


int main()
{
    char nothing[10];
    fgets(nothing,10,stdin);


    scanf("%d %d", &w, &h);
    int board[h][w];
    int dynamic[h][w];


    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            scanf("%d", &board[i][j]);

    if (w==0 || h==0)
        printf("0");
    else
        printf("%d", longest_snake(board, dynamic));
       
    return 0;
}
