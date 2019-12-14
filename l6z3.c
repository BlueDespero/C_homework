#include<stdio.h>
#pragma GCC diagnostic ignored "-Wunused-result"

struct block
{
    int w,h;
    int tab[11][11];
};

int m, n, num_blocks;

/*
void zrob_plansze(int plansza[n][m])
{
    printf("\n\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("%d", plansza[i][j]);
        }
        printf("\n");
    }
}
*/
int zmiana(int plansza[n][m], struct block blok, int miejsce)
{
    int kolizja = 0, wysokosc = n-blok.h;

    for (int i = 0; i <= n-blok.h && kolizja == 0; i++)
    {

        for (int s = 0; s < blok.h && kolizja == 0; s++)
        {
            for (int d = 0; d < blok.w && kolizja == 0; d++)
            {
                if (blok.tab[s][d] == 1 && plansza[i+s+1][d+miejsce] == 1)
                {
                    /*
                    if (move == 2)
                        printf("\n%d %d  ||  %d %d  ||  %d %d\n",s,d,s+i,d+miejsce, i, miejsce);
                    */
                    kolizja = 1;
                }

            }
        }
        
        if (kolizja == 1)
            wysokosc = i;
    }
    
    for (int i = 0; i < blok.h; i++)
        for (int j = 0; j < blok.w; j++)
            if (blok.tab[i][j] == 1)
                plansza[wysokosc+i][miejsce+j] = blok.tab[i][j];

    /*
    if (move == 2)
    {   
        printf("Wysokosc:%d\n", wysokosc);
        zrob_plansze(plansza);                
    }
    */    
    return wysokosc;
}


int make_moves(int move, struct block blocks[], int permutacje[], int plansza[n][m])
{
    if (move < num_blocks)
    {
        int best = 0;
        for (int i = 0; i < (m - blocks[permutacje[move]].w+1); i++)
        {
            int nowa_plansza[n][m];
            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++)
                    nowa_plansza[i][j] = plansza[i][j];

            int aktualna_wysokosc = zmiana(nowa_plansza, blocks[permutacje[move]], i);
            if(aktualna_wysokosc < blocks[permutacje[move]].h)
            {
                //printf("Uciete");
                continue;                
            }

        
            int challenger = make_moves(move+1, blocks, permutacje, nowa_plansza);
            if (challenger > best)
                best = challenger;
        }
        return best;
    }
    else
    {
        int wynik = 0;
        for (int i = 0; i < n; i++)
        {
            int pelen = 1;
            for (int j = 0; j < m; j++)
                if (plansza[i][j] == 0)
                    pelen = 0;
            wynik+=pelen;
        }
        return wynik;
    }
}

int play_tetris(struct block blocks[], int permutacje[])
{
    int plansza[n][m];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            plansza[i][j] = 0;
    int res = make_moves(0, blocks, permutacje, plansza);

    return res;
}

int main() {
    struct block blocks[10];
    int permutacje[10][10];

    scanf("%d %d %d", &m, &n, &num_blocks);

    for (int i = 0; i < num_blocks; i++)
    {
        int w,h;
        scanf("%d %d", &w, &h);
        blocks[i].w = w;
        blocks[i].h = h;

        for (int j = 0; j < h; j++)
        {
            for (int k = 0; k < w; k++)
            {
                char b = 'a';
                while (b!='.' && b!='#')
                    scanf("%c", &b);

                if (b=='.')
                    blocks[i].tab[j][k] = 0;
                else
                    blocks[i].tab[j][k] = 1;
            }
        }
    }

    
    int num_tests;
    scanf("%d", &num_tests);
    for (int i = 0; i < num_tests; i++)
        for (int j = 0; j < num_blocks; j++)
            scanf("%d", &permutacje[i][j]);

    for (int i = 0; i < num_tests; i++)
        printf("%d ", play_tetris(blocks, permutacje[i]));
    
    
    return 0;
}