#include <stdio.h>
int main()
{
    int n = 6, i, j;
    int a[6] = {2, 6, 3, 4, 1, 5};
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                int tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
                //   printf ("%d ",tmp);
            }
        }
    }

    for (i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
}