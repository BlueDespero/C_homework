#include<stdio.h>
#include<stdbool.h>

int m,n, num_l = 0, num_s = 0;

struct coords
{
    int a;
    int b;
};

struct coords lairs[100];
struct coords evid[12];
bool maski[100][100][1<<12];


int state_to_int(bool state[num_s])
{
    int result = 0;
    for (int i = 0; i < num_s; i++)
        result = result*2 + state[i];
    return result;
}

int change_state(int y, int x)
{
    for (int i = 0; i < num_s; i++)
        if (evid[i].a == y && evid[i].b==x)
            return i;
    return 0;
}

void reverse_state(int y, int x, bool state[num_s])
{
    for (int i = 0; i < num_s; i++)
        if (evid[i].a == y && evid[i].b==x)
        {
            state[i]=0;
            break;
        }
}

void dfs(int y, int x, bool state[num_s], int tab[n+5][m+5])
{
    if(tab[y][x] == 2)
    {
        int o = change_state(y,x);
        if (state[o] == 1)
            return;
        state[o]=1;
    }

    int numeric_state = state_to_int(state);

    if (maski[y][x][numeric_state] != 1)
    {
        //printf("%d %d %d %d \n",y,x, numeric_state, tab[y][x]);

        maski[y][x][numeric_state] = 1;

        if (y>0)
            if (tab[y-1][x]!=1)
                dfs(y-1,x,state,tab);

        if (y<n-1 && tab[y+1][x]!=1)
            dfs(y+1,x,state,tab);

        if (x>0)
            if (tab[y][x-1]!=1)
                dfs(y,x-1,state,tab);

        if (x<m-1 && tab[y][x+1]!=1)
            dfs(y,x+1,state,tab);
    }

    if(tab[y][x] == 2)
        reverse_state(y,x,state);
}

int main() {
    scanf("%d %d",&m, &n);
    int tab[n+5][m+5];


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
                struct coords e = {i,j};
                evid[num_s] = e;
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

    int num_max = (1<<(num_s))-1;
    
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            for (int k = 0; k < num_max; k++)
                maski[i][j][k] = 0;

    for (int i = 0; i < num_l; i++)
    {
        bool state[num_s];
        for (int j = 0; j < num_s; j++)
            state[j]=0;
            
        dfs(lairs[i].a, lairs[i].b, state, tab);
    }

    printf("\n%d\n", num_max);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (tab[i][j] == 1)
                printf("#");
            else if (maski[i][j][num_max] == 1)
                printf("X");
            else
                printf(".");
        }
        printf("\n");
    }
    
    
}