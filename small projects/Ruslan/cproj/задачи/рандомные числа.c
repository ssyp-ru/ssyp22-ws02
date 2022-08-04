#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    srand(time(NULL));
    int c;
for (c = 0;c < 10;c++ )
    printf("%d\n", 80 + rand()%(100 - 1 + 1));

} 
