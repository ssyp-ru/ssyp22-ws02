#include <stdio.h>

int main(void){
    int p1a;
    int p1b;
    int p2a;
    int p2b;
    int p1 = p1a + p1b;
    int p2 = p2a + p2b;
    
    scanf ("%d %d %d %d" ,&p1a,&p1b,&p2a,&p2b);
    if(p1a == p1b){
    printf ("первая пара равна: да\n");
    }
    else{
        printf ("первая пара равна: нет\n");
    }
    if(p2a == p2b){
    printf ("вторая пара равна: да\n");
    }
    else{
        printf ("вторая пара равна: нет\n");
    }
    if(p2a+p2a == p1b+p1a){
    printf ("обе пары равны: да\n");
    }
    else{
        printf ("обе пары равны: нет\n");
    }
    if(p2a+p2a != p1b+p1a){
    printf ("обе пары неравны: да\n");
    }
    else{
        printf ("обе пары неравны: нет\n");
    }
    if(p2 < p1){
    printf ("Сумма чисел из первой пары больше суммы чисел из второй пары: да\n");
    }
    else{
        printf ("Сумма чисел из первой пары больше суммы чисел из второй пары: нет\n");
    }
    
    return 0;
}
     
