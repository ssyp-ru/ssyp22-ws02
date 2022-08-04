#include <stdio.h>

int main()
{
    int num1;
    int num2;
    int num3;
    printf ("Введите три числа через пробел и нажмите Enter:");
    scanf ("%d%d%d\n",&num1 ,&num2 ,&num3);
    if(num2 < num1){
        if (num1 > num3){
        printf ("Самое большое число %d\n",num1);
        }
        else{
        printf ("Самое большое число %d\n",num3);
        }
    }
    else{
         if (num2 > num3){
        printf ("Самое большое число %d\n",num2);
        }
        else{
        printf ("Самое большое число %d\n",num3);
        }
    }
    
    
    return 0;
} 
