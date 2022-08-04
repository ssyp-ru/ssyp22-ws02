#include <stdio.h>



int main(void){
    int s = 3;
    int k = 3;
    char karta[s][k];
    for (int str = 0;str<s;str++){
        for (int kol = 0;kol<k;kol++){
            karta[str][kol] = '#';
            
        }
        
    }
    

       
    for (int str = 1;str<s-1;str++){
        for (int kol = 1;kol<k-1;kol++){
            karta[str][kol] = '.';
            
        }
        
    }
    
    
 
            karta[s/2][k/2] = '@';
            

    
    for (int str = 0; str < s; str++){
        for (int kol = 0; kol < k; kol++){
            printf("%c", karta[str][kol]);
        }
        printf ("\n");
    }
} 
