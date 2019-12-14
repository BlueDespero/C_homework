#include<stdio.h>
#include<stdbool.h>

int m,n, num_l = 0, num_s = 0;
//int iter = 1;

struct coords
{
    unsigned char a;
    unsigned char b;
};

void add_possibilities(int y, int x, unsigned char result[n][m], unsigned char tab[n][m])
{
    if (result[y][x] != 6)
    {
        result[y][x] = 6;

        if (y<n-1 && tab[y+1][x]!=1 && tab[y+1][x]!=2)
            add_possibilities(y+1,x, result, tab);

        if (y>0 && tab[y-1][x]!=1 && tab[y+1][x]!=2)
            add_possibilities(y-1,x, result, tab);        
        
        if (x<m-1 && tab[y][x+1]!=1 && tab[y+1][x]!=2)
            add_possibilities(y,x+1, result, tab);

        if (x>0 && tab[y][x-1]!=1 && tab[y+1][x]!=2)
            add_possibilities(y,x-1, result, tab);
    }
}

void dfs(int y, int x, bool visited[n][m], unsigned char tab[n][m], unsigned char result[n][m], int to_visit)
{
    visited[y][x] = 1;

    /*
    for(int i = 0;i<n;i++)
    {
        for(int j = 0;j<m;j++)
            printf("%d", visited[i][j]);
        printf("\n");         
    }
    fflush(stdout);
    printf("\n");
    */

    //printf("%d\n",iter);
    //iter++;

    if (tab[y][x] == 2)
    {
        to_visit--;

        if (to_visit == 0)
            add_possibilities(y,x, result, tab);
        else
        {
            for(int i = 0;i<n;i++)
                for(int j = 0;j<m;j++)
                    if (tab[i][j]!=2)
                        visited[i][j]=0;            
        }
    }
    
    if (y<n-1 && tab[y+1][x]!=1 && visited[y+1][x]!=1)
        dfs(y+1,x,visited,tab, result, to_visit);
    //printf("\n0");fflush(stdout);

    if (y>0 && tab[y-1][x]!=1 && visited[y-1][x]!=1)
        dfs(y-1,x,visited,tab, result,to_visit);        
    //printf("1");fflush(stdout);

    if (x<m-1 && tab[y][x+1]!=1 && visited[y][x+1]!=1)
        dfs(y,x+1,visited,tab, result,to_visit);
    //printf("2");fflush(stdout);

    if (x>0 && tab[y][x-1]!=1 && visited[y][x-1]!=1)
        dfs(y,x-1,visited,tab, result,to_visit);
    //printf("3\n");fflush(stdout);

    visited[y][x] = 0;
}

void slover(unsigned char tab[n][m], unsigned char result[n][m], struct coords lairs[])
{
    for (int i = 0; i < num_l; i++)
    {
        int y = lairs[i].a; 
        int x = lairs[i].b;

        bool visited[n][m];
        for(int i = 0;i<n;i++)
            for(int j = 0;j<m;j++)
                visited[i][j]=0;    
        printf("%d\n",i);
        fflush(stdout);
        dfs(y,x,visited,tab, result, num_l);
    }
}

int main() {
    scanf("%d %d",&m, &n);
    unsigned char tab[n][m];
    unsigned char result[n][m];
    struct coords lairs[100];

    char line[m+10];
    fgets(line, m+10, stdin);
    for (int i = 0; i < n; i++)
    {
        fgets(line,m+10,stdin);

        for (int j = 0; j < m; j++)
        {
            if (line[j] == '.')
                tab[i][j] = 0;
            else if (line[j] == '#')
                tab[i][j] = 1;
            else if (line[j] == 'S')
            {
                tab[i][j] = 2;
                num_s++;                
            }
            else if (line[j] == 'L')
            {
                tab[i][j] = 3;
                struct coords lair = {i,j};
                lairs[num_l] = lair;
                num_l++;                
            }
        }
    }

    for(int i = 0;i<n;i++)
        for(int j = 0;j<m;j++)
            result[i][j]=tab[i][j];

    slover(tab, result, lairs);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (result[i][j] == 6)
                printf("X");
            else if (tab[i][j] == 1)
                printf("#");
            else
                printf(".");
        }
        printf("\n");
    }
    

    /*
    printf("\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            printf("%d", tab[i][j]);
        printf("\n");
    }
    */

    return 0;
}