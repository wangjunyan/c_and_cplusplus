#include<stdio.h>

void print_optimal(int s[][6], int i, int j)
{
	if (i == j)
	{
		printf("A%d", i);
	}
	else
	{
		printf("(");
		print_optimal(s, i, s[i][j]-1);
		print_optimal(s, s[i][j], j);
		printf(")");
	}
}

void matrix_chain_order(int *p, int n)
{
	int i, j, k, l, q;
	int m[6][6];
	int s[6][6];
	for(i=0;i<6;i++)
		for(j=0;j<6;j++)
			m[i][j]=0;
	for(i=0;i<6;i++)
		for(j=0;j<6;j++)
			s[i][j]=0;

	for (i = 0; i < n; i++)
	{
		m[i][i] = 0;
	}
	for (l = 2; l <= n; l++)
	{
		for (i = 0; i < n-l+1; i++)
		{
			j = i+l-1;
			m[i][j] = 99999;
			for (k = i; k < j; k++)
			{
				q = m[i][k] + m[k+1][j] + p[i]*p[k+1]*p[j+1];
				if (q < m[i][j])
				{
					m[i][j] = q;
					s[i][j] = k+1;
				}
			}
		}
	}

	printf("------ m ------\n");
	for(i = 0; i < 6; i++)
	{
		for(j = 0; j < 6; j++)
		{
			printf("%d\t", m[i][j]);
		}
		printf("\n");
	}
	printf("------ s ------\n");
	for(i = 0; i < 6; i++)
	{
		for(j = 0; j < 6; j++)
		{
			printf("%d\t", s[i][j]);
		}
		printf("\n");
	}
	printf("------ output ------\n");
	print_optimal(s, 0, 5);
	printf("\n");
}

int main()
{
	int p[7] = {30, 35, 15, 5, 10, 20, 25};
	int n = 6;
	matrix_chain_order(p, n);
	return 0;
}
