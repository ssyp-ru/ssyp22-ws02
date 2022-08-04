#include <stdio.h>
#include <stdlib.h>

int summa(int a, int b, int c){
    return a + b + c;
}

int main(void){
    long s = 65777787856; 
    printf("Privet: %ld, %ld\n", s, summa(5,5,5));
    char data[] = "Vkusnyashka";
    printf("Data: %s\n", data);
    return 0;
}
