#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int max(int a, int b)
{
    if (a <= b)
        return b;
    else
        return a;
}


int cut_rod(int *p, int n)
{
    int i;
    int q = -999;
    if (n == 0)
        return 0;
    for (i=1; i<=n; i++)
    {
        q = max(q, p[i-1] + cut_rod(p, n-i));
    }
    return q;
}

int mem_cut_rod_aux(int *p, int n, int *r)
{
    int q, i;
    if (r[n] >= 0)
        return r[n];
    if (n == 0)
    {
        q = 0;
    }
    else
    {
        q = -999;
        for (i=1; i<=n; i++)
        {
            q = max(q, p[i-1] + mem_cut_rod_aux(p, n-i, r));
        }
    }
    r[n] = q;
    return q;
}

int mem_cut_rod(int *p, int n)
{
    int *r = (int *)malloc(sizeof(int)*(n+1));
    int i;
    for (i=0; i<=n; i++)
        *(r+i) = -999;
    return mem_cut_rod_aux(p, n, r);
}

int bottom_up_cut_rod(int *p, int n)
{
    int i, j, q;
    int *r = (int *)malloc(sizeof(int)*(n+1));
    r[0] = 0;
    for (j=1; j<=n; j++)
    {
        q = -999;
        for(i=1; i<=j; i++)
        {
            q = max(q, p[i-1] + r[j-i]);
        }
        r[j] = q;
    }
    for (i=0; i<n; i++)
        printf("r[%d]=%d\n", i, r[i]);
    return r[n];
}

int main()
{
    int p[10] = {1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    int q = cut_rod(p, 4);
    printf("cut_rod: q = %d\n", q);
    q = mem_cut_rod(p, 4);
    printf("mem_cut_rod: q = %d\n", q);
    q = bottom_up_cut_rod(p, 10);
    printf("bottom_up_cut_rod: q = %d\n", q);
    return 0;
}
