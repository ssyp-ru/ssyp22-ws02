#include <stdio.h>

int main()
{
    int num1;
    int num2;
    int num3;
    printf ("Введите три числа через пробел и нажмите Enter:");
    scanf ("%d%d%d\n",&num1 ,&num2 ,&num3);
    if (num1 == num2){
        if(num2 == num3){
            printf ("три числа равны\n");
        }
        
    }
    else{
        if(num2 < num1){
            if (num1 > num3){
            printf ("Самое большое число первое\n");
            }
            else{
            printf ("Самое большое число третье\n");
            }
        }
        else{
            if (num2 > num3){
            printf ("Самое большое число второе\n");
            }
            else{
            printf ("Самое большое число третье\n");
            }
        }
        if(num2 > num1){
            if (num1 < num3){
            printf ("Самое маленькое число первое\n");
            }
            else{
            printf ("Самое маленькое число третье\n",num3);
            }
        }
        else{
            if (num2 > num3){
            printf ("Самое маленькое число второе\n",num2);
            }
            else{
            printf ("Самое маленькое число третье\n",num3);
            }
    }
  } 
