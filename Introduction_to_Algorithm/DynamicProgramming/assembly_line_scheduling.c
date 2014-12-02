#include<stdio.h>

int min(int a, int b)
{
    if(a <= b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

void print_a(int a[][6])
{
    int i,j;
    for(i=0; i<2; i++)
    {
        for(j=0; j<6; j++)
        {
            printf("%d\t", a[i][j]);
        }
        printf("\n");
    }
}

void fastest_way(int a[][6], int t[][5], int *e, int *x, int n)
{
    int i, j;
    int f_min, l_min;
    int f1[6], f2[6], l1[6], l2[6];
    f1[0] = e[0] + a[0][0];
    f2[0] = e[1] + a[1][0];
    l1[0] = 1;
    l2[0] = 2;
    for (j = 1; j < 6; j++)
    {
        if (f1[j-1] + a[0][j] <= f2[j-1] + t[1][j-1] + a[0][j])
        {
            f1[j] = f1[j-1] + a[0][j];
            l1[j] = 1;
        }
        else
        {
            f1[j] = f2[j-1] + t[1][j-1] + a[0][j];
            l1[j] = 2;
        }


        if (f2[j-1] + a[1][j] <= f1[j-1] + t[0][j-1] + a[1][j])
        {
            f2[j] = f2[j-1] + a[1][j];
            l2[j] = 2;
        }
        else
        {
            f2[j] = f1[j-1] + t[0][j-1] + a[1][j];
            l2[j] = 1;
        }
    }

    if (f1[5] + x[0] <= f2[5] + x[1])
    {
        f_min = f1[5] + x[0];
        l_min = 1;
    }
    else
    {
        f_min = f2[5] + x[1];
        l_min = 2;
    }


    printf("f_min = %d\tl_min = %d\n", f_min, l_min);
    printf("f1:\t");
    for (i = 0; i < 6; i++)
    {
        printf("%d\t", f1[i]);
    }
    printf("\n");


    printf("f2:\t");
    for (i = 0; i < 6; i++)
    {
        printf("%d\t", f2[i]);
    }
    printf("\n");

    printf("l1:\t");
    for (i = 0; i < 6; i++)
    {
        printf("%d\t", l1[i]);
    }
    printf("\n");

    printf("l2:\t");
    for (i = 0; i < 6; i++)
    {
        printf("%d\t", l2[i]);
    }
    printf("\n");
}

int main()
{
    int n = 6;
    int a[2][6] = {{3, 8, 6, 3, 4, 2},{5, 10, 2, 2, 5, 3}};
    int t[2][5] = {{2, 1, 2, 1, 2}, {3, 4, 1, 1, 3}};
    int e[2] = {4, 3};
    int x[2] = {4, 6};
    print_a(a);
    printf("----------\n");
    fastest_way(a, t, e, x, n);
    return 0;
}

