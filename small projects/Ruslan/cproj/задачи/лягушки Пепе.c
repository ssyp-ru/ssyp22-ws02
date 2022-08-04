#include <stdio.h>

int main(void)
{
    int k;
    int kv = 0;
    int v;
    int l;
    printf("Сколько ВСЕГО лягушек Пепе может поместиться в коробке? :" );    
    scanf("%d\n", &k);
    while(1)
    {
     printf(" Сколько лягушек вы положите в коробку? :" );    
     scanf("%d\n", &v);
     kv = kv + v;
     l = kv - k;
     if(kv > k) {
        printf("Коробка заполнилась!" );
        printf("В неё не влезло %d лягушек!\n", l );
        break;
     }
    }
    
    
    
    return 0;
}
 
