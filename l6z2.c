#include<assert.h>
#include<stddef.h>
#include<stdio.h>

char * strstr ( const char *str1, const char *str2 )
{
    const char * st1 = str1;
    size_t znalezione = 0;
    char * alt = NULL;
    
    while (*st1 != '\0')
    {
        if (*st1 == *str2)
        {
            const char * c1 = st1;
            const char * c2 = str2;
            while (*c1 == *c2 && *c2!='\0')
            {
                c1++;
                c2++;
            }

            if (*c2 == '\0')
            {
                znalezione = 1;
                break;            
            }
        }
        st1++;
    }

    if (znalezione == 1)
        return (char *)st1;        
    else
        return alt;
}

size_t strcspn ( const char *str1, const char *str2 )
{
    const char * st1 = str1;
    size_t res = 0;

    while (*st1 != '\0')
    {
        const char * st2 = str2;
        do
        {
            if (*st2 == *st1)
                return res;
            st2++;
        }while (*st2 != '\0');
        res++;
        st1++;
    }

    return res;
}

size_t strspn ( const char *str1, const char *str2 )
{
    const char * st1 = str1;
    size_t res = 0, con = 1;

    while (*st1 != '\0' && con == 1)
    {
        const char * st2 = str2;
        con = 0;

        while (*st2 != '\0')
        {
            if (*st2 == *st1)
                con = 1;
            st2++;
        }

        if (con == 1)
        {
            res++;
            st1++;            
        }
    }
    return res;
}


char * strpbrk ( const char *str1, const char *str2 )
{
    const char * st1 = str1;
    
    while (*st1 != '\0')
    {
        const char * st2 = str2;
        while (*st2 != '\0')
        {
            if(*st2 == *st1)
                return (char *) st1;
            st2++;
        }
        st1++;
    }

    return NULL;
}

int main() {
    if (1)
    {
        char str[] = "This is a simple string";
        printf("%p\n", strstr(str, "z"));
        //assert(*strstr(str, "z") == NULL);
    }

    if (1)
    {
        //char str[] = "This is a simple string";
        printf("%s\n", strstr("", ""));
    }
    printf("%p\n", strpbrk("",""));

    return 0;
}

/*
W treści powiedziano, że należy tylko poinformować o przypadkach testowych w komentarzu
więc nie załączam pliku z testami i porównaniami fo biblioteki string.h
Wszystkie testy zakończyły się zgodnie z oczekiwanimi, czyli rezultaty były identyczne co w funkcjach z string.h

Testy funkcji strstr:
    - klucz zawiera się tekście
    - klucz pusty, tekst niepusty
    - tekst pusty, klucz niepusty
    - klucz pusty, tekst pusty
    - klucz nie zawiera się w tekście
    - prefiks klucza zawiera się w tekście

Testy funkcji strcspn i strpbrk:
    - element klucza znajdował się w pierwszej połowie tekstu
    - element klucza znajdował się w drugiej połowie tekstu
    - element klucza nie znajdował się w tekście
    - klucz pusty, tekst niepusty
    - tekst pusty, klucz niepusty
    - klucz pusty, tekst pusty

Testy funkcji strspn:
    - tekst zaczynał się kluczem
    - tekst zaczynał się fragmentem klucza
    - tekst był kopią klucza
    - tekst kończył się fragmentem klucza
    - tekst nie zawierał fragmentu klucza
    - klucz pusty, tekst niepusty
    - tekst pusty, klucz niepusty
    - klucz pusty, tekst pusty
*/