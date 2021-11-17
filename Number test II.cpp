#include <stdio.h>
#include <math.h>

long long int V[4475], n;
int k = 1;

int bb (long long int A[], int i, int j, int n)
{
	if (i>j)
	return j;
	int m = ((i+j)/2);
	if (A[m] == n)
	return m;
	else {
		if (n > A[m])
		bb (A, m + 1, j, n);
		else
		bb (A, i, m-1, n);
	}
}

int main (void)
{
	for (int i = 1, x = 1; i < 4474; i++, x += i)
	V[i] = x;
	while (scanf ("%lli", &n) == 1)
	{
		int cont = 0;
		do {
			k = bb (V, 1, 100, n);
			cont++;
			printf ("huevos ");
			n -= V[k];
		} while (n != 0);
		printf ("%d\n", cont);
	}
	return 0;
}
