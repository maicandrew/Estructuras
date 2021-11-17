#include <stdio.h>

int V[4500];

int bb(int A[], int i, int j,int n);


int bb(int A[], int i, int j,int n)
{
	if(i>j)
	return -j;
	else
	{
		int m=(i+j)/2;
		if(A[m]==n)
			return m;
		else
		{
		if(n>A[m])
			bb(A,m+1,j,n);
		else
			bb(A,i,m-1,n);
		}
	}
}

int main()
{
	for(int i=1,x=1; i<=4500; i++,x=x+i)
	V[i] = x;
	int n;
	while (scanf ("%d", &n)) {
		int j = bb(V, 0, 4500, n);
		if (j < 0)
			j *= -1;
		printf ("%d ", V[j+1]-n);
		printf ("%d", j+1);
		printf ("\n");
	}
}
