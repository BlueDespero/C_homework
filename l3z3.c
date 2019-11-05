#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int bok;

void from_diagonal(int image[1024][1024])
{
    int suma = 0, p = 0, direction = -1, stan = 0, iter = 0;
    scanf("%d",&bok);

    int a = 0, b = 0;
    while (suma<(bok*bok))
    {
        scanf("%d", &p);
        suma+=p;

        for (int i = 0; i < p; i++)
        {
            iter++;
            image[a][b] = stan;
            a+=direction; b-=direction;
            
            if (iter < (((1+bok)*bok)/2))
            {
                if (a<0)
                {
                    a+=1;
                    direction*=(-1);
                } 
                if (b<0)
                {
                    b+=1;
                    direction*=(-1);
                }
            }
            else
            {
                if (a==bok)
                {
                    a-=1;
                    b+=2;
                    direction*=(-1);
                } 
                if (b==bok)
                {
                    b-=1;
                    a+=2;
                    direction*=(-1);
                }   
            }
        }
        stan=(stan+1)%2;
    }
}

int to_diagonal(int image[1024][1024])
{
    int direction = -1;
    int a = 0, b = 0, result = 1, now = image[0][0];

    if (image[0][0] == 1) result++;

    for (int i = 0; i < (bok*bok); i++)
    {
        if (now != image[a][b])
            result+=1;
        now = image[a][b];
        a+=direction; b-=direction;


        if (i+1 < (((1+bok)*bok)/2))
        {
            if (a<0)
            {
                a+=1;
                direction*=(-1);
            } 
            if (b<0)
            {
                b+=1;
                direction*=(-1);
            }
        }
        else
        {
            if (a==bok)
            {
                a-=1;
                b+=2;
                direction*=(-1);
            } 
            if (b==bok)
            {
                b-=1;
                a+=2;
                direction*=(-1);
            }   
        }
    }
    return result;
}

void from_row(int image[1024][1024])
{
    int suma = 0, p = 0, stan = 0;
    scanf("%d",&bok);

    int a = 0, b = 0;
    while (suma<(bok*bok))
    {
        scanf("%d", &p);
        suma+=p;
        for (int i = 0; i < p; i++)
        {
            image[a][b] = stan;
            b+=1;

            if (b == bok)
            {
                b = 0;
                a+=1;
            }
        }
        stan=(stan+1)%2;
    }
}

int to_row(int image[1024][1024])
{
    int a = 0, b = 0, now = image[0][0], result = 1;

    if (image[0][0] == 1) result++;


    for (int i = 0; i < (bok*bok); i++)
    {
        if (now != image[a][b])
            result+=1;
        now = image[a][b];

        b+=1;
        if (b == bok)
        {
            b = 0;
            a+=1;
        }
    }
    return result;
}

void from_snake(int image[1024][1024])
{
    int suma = 0, p = 0, direction = -1, stan = 0, iter = 0;
    scanf("%d",&bok);

    int a = 0, b = 0;
    while (suma<(bok*bok))
    {
        scanf("%d", &p);
        suma+=p;
        for (int i = 0; i < p; i++)
        {
            if (iter%bok == 0 && iter!=0)
                a+=1;

            image[a][b] = stan;
            b-=direction;

            if (b<0)
            {
                direction*=(-1);  
                b+=1;              
            }
            else if (b==bok)
            {
                direction*=(-1);  
                b-=1;
            }
            iter+=1;
        }
        stan=(stan+1)%2;
    }
}

int to_snake(int image[1024][1024])
{
    int direction = -1, now = image[0][0], result = 1;
    int a = 0, b = 0;

    if (image[0][0] == 1) result++;

    for (int i = 0; i < (bok*bok); i++)
    {
        if (i%bok == 0 && i!=0)
            a+=1;

        if (now != image[a][b])
            result+=1;
        now = image[a][b];

        b-=direction;
        if (b<0)
        {
            direction*=(-1);  
            b+=1;              
        }
        else if (b==bok)
        {
            direction*=(-1);  
            b-=1;
        }
    }

    return result;
}

void from_normal(int image[1024][1024])
{
    char c1[10],c2[10];
    char c;
    char * end;
    int iter = 0;
    long a,b;

    while (!(isspace(c = getchar())))
    {
        c1[iter] = c;
        iter+=1;
    }
    c1[iter]='\0';
    a = strtol(c1, &end, 10);    

    while (isspace(c = getchar()));

    iter = 0;
    do
    {
        c2[iter] = c;
        iter+=1;
    } while (!(isspace(c = getchar())));
    c2[iter]='\0';
    b = strtol(c2, &end, 10);

    bok = a;
    long row_size = 0, column_size = 0;
    
    while (column_size<b)
    {
        while (row_size<a)
        {
            char p;
            while (isspace((p = getchar())));
            image[column_size][row_size] = p-48;
            row_size+=1;
        }
        row_size=0;
        column_size+=1;
    }
}

void load_image(char mode[], int image[1024][1024])
{
    switch (mode[1])
    {
    case '1':
        from_normal(image);
        break;
    case 'R':
        from_row(image);
        break;
    case 'S':
        from_snake(image);
        break;
    case 'D':
        from_diagonal(image);
        break;
    default:
        printf("\nERROR\n");
        break;
    }
}

int main(void)
{
    int image[1024][1024];
    char mode[10];
    fgets(mode, 10, stdin);

    load_image(mode, image);
    printf("%d %d %d",to_row(image), to_snake(image), to_diagonal(image));
    return 0;
}