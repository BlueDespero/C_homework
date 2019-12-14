#include<string.h>
#include<assert.h>

int main() {
    //strcmp
    assert(strcmp("","") == 0);
    assert(strcmp("","A") == -1);
    assert(strcmp("A","") == 1);
    assert(strcmp("A","A") == 0);
    assert(strcmp("AaBb","AaBb") == 0);
    assert(strcmp("AAbb","aaBB") == -1);
    assert(strcmp("AAa","AA") == 1);
    assert(strcmp("01","10") == -1);

    //strncmp
    assert(strncmp("","",0) == 0);
    assert(strncmp("","A",0) == 0);
    assert(strncmp("A","",0) == 0);
    assert(strncmp("A","A",0) == 0);
    assert(strncmp("AaBb","AaBb",0) == 0);
    assert(strncmp("AAbb","aaBB",0) == 0);
    assert(strncmp("AAa","AA",0) == 0);
    assert(strncmp("01","10",0) == 0);

    assert(strncmp("","",1) == 0);
    assert(strncmp("","A",1) == -1);
    assert(strncmp("A","",1) == 1);
    assert(strncmp("A","A",1) == 0);
    assert(strncmp("AaBb","AaBb",1) == 0);
    assert(strncmp("AAbb","aaBB",1) == -1);
    assert(strncmp("AAa","AA",1) == 0);
    assert(strncmp("01","10",1) == -1);

    assert(strncmp("","",2) == 0);
    assert(strncmp("","A",2) == -1);
    assert(strncmp("A","",2) == 1);
    assert(strncmp("A","A",2) == 0);
    assert(strncmp("AaBb","AaBb",2) == 0);
    assert(strncmp("AAbb","aaBB",2) == -1);
    assert(strncmp("AAa","AA",2) == 0);
    assert(strncmp("01","10",2) == -1);

    //strcat
    if (1)
    {
        char str[30] = "";
        const char *strFrom = ""; 
        assert(strcmp(strcat(str,strFrom), "") == 0);

        char str1[30] = "A";
        const char *strFrom1 = ""; 
        assert(strcmp(strcat(str1,strFrom1), "A") == 0);
    
        char str2[30] = "";
        const char *strFrom2 = "A"; 
        assert(strcmp(strcat(str2,strFrom2), "A") == 0);
    
        char str3[30] = " ";
        const char *strFrom3 = " "; 
        assert(strcmp(strcat(str3,strFrom3), "  ") == 0);
    
        char str4[30] = "A";
        const char *strFrom4 = " "; 
        assert(strcmp(strcat(str4,strFrom4), "A ") == 0);
    }
    

    if (1)
    {
        char str[30] = "AA";
        const char *strFrom = "AA"; 
        assert(strcmp(strcat(str,strFrom), "AAAA") == 0);

        char str1[30] = "A";
        const char *strFrom1 = "a"; 
        assert(strcmp(strcat(str1,strFrom1), "Aa") == 0);
    
        char str2[30] = "a";
        const char *strFrom2 = "A"; 
        assert(strcmp(strcat(str2,strFrom2), "aA") == 0);
    
        char str3[30] = " ";
        const char *strFrom3 = " a"; 
        assert(strcmp(strcat(str3,strFrom3), "  a") == 0);
    
        char str4[30] = "A";
        const char *strFrom4 = " a"; 
        assert(strcmp(strcat(str4,strFrom4), "A a") == 0);
    }

    //strncat
    if (1)
    {
        char str[30] = "";
        const char *strFrom = ""; 
        assert(strcmp(strncat(str,strFrom,0), "") == 0);

        char str1[30] = "A";
        const char *strFrom1 = ""; 
        assert(strcmp(strncat(str1,strFrom1,0), "A") == 0);
    
        char str2[30] = "";
        const char *strFrom2 = "A"; 
        assert(strcmp(strncat(str2,strFrom2,0), "") == 0);
    
        char str3[30] = " ";
        const char *strFrom3 = " "; 
        assert(strcmp(strncat(str3,strFrom3,0), " ") == 0);
    
        char str4[30] = "A";
        const char *strFrom4 = " "; 
        assert(strcmp(strncat(str4,strFrom4,0), "A") == 0);
    }

    if (1)
    {
        char str[30] = "AA";
        const char *strFrom = "AA"; 
        assert(strcmp(strncat(str,strFrom,1), "AAA") == 0);

        char str1[30] = "A";
        const char *strFrom1 = "a"; 
        assert(strcmp(strncat(str1,strFrom1,1), "Aa") == 0);
    
        char str2[30] = "a";
        const char *strFrom2 = "A"; 
        assert(strcmp(strncat(str2,strFrom2,1), "aA") == 0);
    
        char str3[30] = " ";
        const char *strFrom3 = " a"; 
        assert(strcmp(strncat(str3,strFrom3,1), "  ") == 0);
    
        char str4[30] = "A";
        const char *strFrom4 = " a"; 
        assert(strcmp(strncat(str4,strFrom4,1), "A ") == 0);
    }

    if (1)
    {
        char str[30] = "AA";
        const char *strFrom = "AA"; 
        assert(strcmp(strncat(str,strFrom,2), "AAAA") == 0);

        char str1[30] = "A";
        const char *strFrom1 = "a"; 
        assert(strcmp(strncat(str1,strFrom1,2), "Aa") == 0);
    
        char str2[30] = "a";
        const char *strFrom2 = "A"; 
        assert(strcmp(strncat(str2,strFrom2,2), "aA") == 0);
    
        char str3[30] = " ";
        const char *strFrom3 = " a"; 
        assert(strcmp(strncat(str3,strFrom3,2), "  a") == 0);
    
        char str4[30] = "A";
        const char *strFrom4 = " a"; 
        assert(strcmp(strncat(str4,strFrom4,2), "A a") == 0);
    }

    if (1)
    {
        char str[30] = "AA";
        const char *strFrom = "AA"; 
        assert(strcmp(strncat(str,strFrom,8), "AAAA") == 0);

        char str1[30] = "A";
        const char *strFrom1 = "a"; 
        assert(strcmp(strncat(str1,strFrom1,8), "Aa") == 0);
    
        char str2[30] = "a";
        const char *strFrom2 = "A"; 
        assert(strcmp(strncat(str2,strFrom2,8), "aA") == 0);
    
        char str3[30] = " ";
        const char *strFrom3 = " a"; 
        assert(strcmp(strncat(str3,strFrom3,8), "  a") == 0);
    
        char str4[30] = "A";
        const char *strFrom4 = " a"; 
        assert(strcmp(strncat(str4,strFrom4,8), "A a") == 0);
    }

    return 0;
}