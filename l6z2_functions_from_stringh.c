#include<stdio.h>
#include<string.h>
#include<assert.h>

int main()
{
    //strstr
    //char * null_pointer = NULL;
    /*
    if (1)
    {
        char str[] = "This is a simple string";
        assert(*strstr(str, "simple") == 's');
    }

    
    if (1)
    {
        char str[] = "This is a simple string";
        printf("%s\n", strstr(str,""));
        //assert(strstr(str, "") == null_pointer);
    }
    
    if (1)
    {
        //char str[] = "This is a simple string";
        printf("%p\n", strstr("", ""));
        //assert(*strstr(str, "z") == NULL);
    }
    
    if (1)
    {
        char str[] = "This is a simple string";
        assert(*strstr(str, "arbuz") == *null_pointer);
    }

    if (1)
    {
        char str[] = "";
        assert(*strstr(str, "simple") == *null_pointer);
    }
    */

    if (1)
    {
        char str[] = "This is a simple string";
        assert(*strstr(str, "simple") == 's');
    }

    if (1)
    {
        char str[] = "fcba73";
        char keys[] = "1234567890";
        int i;
        i = strcspn (str,keys);
        assert(i == 4);
    }
    

    if (1)
    {
        char strtext[] = "129th";
        char cset[] = "1234567890";

        int i = strspn (strtext,cset);
        assert(i == 3);
    }
    

    if (1)
    {
        char str[] = "This is a sample string";
        char key[] = "aeiou";
        char * pch = strpbrk (str, key);
        assert(*pch == 'i');
    }

    printf("%lu\n", strspn("A",""));
    printf("%p\n", strpbrk("A",""));
    printf("%lu\n", strcspn("A",""));

    return 0;
}
