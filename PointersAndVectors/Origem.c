//Felipe Cancella - 2210487

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

unsigned long long** cria2D(int row, int col) 
{
	unsigned long long** mat;
	int i, j, k;
	mat = (unsigned long long**) malloc (row * sizeof (unsigned long long*));
	if (mat == NULL)
		return NULL;
	for (i = 0; i < row; i++) 
	{
		mat[i] = (unsigned long long*) malloc (col * sizeof(unsigned long long));
		if (mat[i] == NULL)
			return NULL;
	}

	for (i = 0; i < row; i++) 
	{
		for (j = 0; j < col; j++) 
		{
			k = col * i + j + 1;
			mat[i][j] = k;
		}
	}
	return mat;
}

unsigned long long** criaC(int row, int col) 
{
	unsigned long long** mat;
	int i, j, k;
	mat = (unsigned long long**)malloc(row * sizeof(unsigned long long*));
	if (mat == NULL)
		return NULL;
	for (i = 0; i < row; i++) {
		mat[i] = (unsigned long long*)malloc(col * sizeof(unsigned long long));
		if (mat[i] == NULL)
			return NULL;
	}

	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			mat[i][j] = 0;
		}
	}
	return mat;
}

void print2D(unsigned long long** v, int row, int col, int max) 
{
	int i, j;
	for (i = 0; i < row && i < max; i++) 
	{
		for (j = 0; j < col && j < max; j++)
			printf("%llu ", v[i][j]);
		printf("\n");
	}
	printf("-\n\n");
	return;
}

void mult1(unsigned long long** a, unsigned long long** b, unsigned long long** c, int n, int m, int w) 
{
	int i, j, k;
	for (i = 0; i < n; i++)
		for (j = 0; j < w; j++)
			for (k = 0; k < m; k++)
				c[i][j] += a[i][k] * b[k][j];

}


void mult2(unsigned long long** a, unsigned long long** b, unsigned long long** c, int n, int m, int w) 
{
	int i, j, k;
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++)
			for (k = 0; k < w; k++)
				c[i][k] += a[i][j] * b[j][k];
}

void libera2D(unsigned long long** v, int row) 
{
	int i;
	for (i = 0; i < row; i++)
		free(v[i]);
}


int main(void) 
{
	unsigned long long** Ma, Mb, Mc;
	int n = 2048, m = 1024, w = 4096, max = 5;
	clock_t t0, t1;
	double elapsed;

	Ma = cria2D(n, m);
	Mb = cria2D(m, w);
	Mc = criaC(n, w);

	t0 = clock();
	//mult1(Ma, Mb, Mc, n, m, w);
	mult2(Ma, Mb, Mc, n, m, w);
	t1 = clock();
	elapsed = 1000 * ((double)t1 - (double)t0) / CLOCKS_PER_SEC;

	if (Ma == NULL || Mb == NULL || Mc == NULL)
	{
		printf("Memoria insuficiente");
		exit(1);
	}

	printf("Matriz A:\n");
	print2D(Ma, n, m, max);

	printf("Matriz B:\n");
	print2D(Mb, m, w, max);

	printf("Matriz C:\n");
	print2D(Mc, n, w, max);

	printf("Tempo em milisegundos: %.4f\n", elapsed);

	libera2D(Ma, n);
	libera2D(Mb, m);
	libera2D(Mc, n);

	system("pause");
	return 0;
}