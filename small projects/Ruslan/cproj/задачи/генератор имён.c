#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()//генератор эльфийских имён
{
char* n[7] = {"ле","го","лас","исс","ыл","дур","да"};   
char* b[6] = {"ни","ель","гол","влей","дил","лу"}; 
char* c[7] = {"чи","ель","эр","лонд","а","ра","горн"};  

    int r;
    int d;
    int v;
    srand(time(NULL));
    v = rand()%(sizeof(c)/sizeof(char*));
    d = rand()%(sizeof(b)/sizeof(char*));
    r = rand()%(sizeof(n)/sizeof(char*));
    printf("%s%s%s", n[r],b[d],c[v]);
    
    
    
} 
