#include <stdio.h>

unsigned int dim_right(unsigned int w){
    return w^(w&-w);}

unsigned int dim_left(unsigned int w){
    unsigned int pos = 0, c = w;
    while (c>0){
        c/=2;
        pos++;}
    return w^(1<<(pos-1));}

unsigned int flip(unsigned int w, unsigned int f){
    if ((w|1<<f)!=w)
        return (w|1<<f);
    return w^(1<<f);}

int main(void){
    unsigned int slowo, f;
    scanf("%u %u",&slowo, &f);
    printf("%u %u %u", dim_right(slowo), dim_left(slowo), flip(slowo,f));
    return 0;}