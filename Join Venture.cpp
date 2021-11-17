#include <stdio.h>
long long unsigned int Lego[1000005];
long long unsigned int L[(1000005/2) +1 ];
long long unsigned int R[(1000005/2) +1 ];

void merge(long long unsigned int arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 =  r - m;

	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1+ j];


	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}


	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
}


void mergeSort(long long unsigned int arr[], int l, int r)
{
	if (l < r)
	{
		int m = l+(r-l)/2;
		mergeSort(arr, l, m);
		mergeSort(arr, m+1, r);
		merge(arr, l, m, r);
	}
}


int bb(long long unsigned int A[], int i, int j,int n)
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


int main ()
{
	
	int ma, k = -1;
	int tam,n;
	while (scanf ("%d", &tam) != EOF && tam >= 1){
	scanf("%d", &n);
	if(n!=0)
	{
	for(int i=1; i<=n; i++)
	{
		scanf("%llu", &Lego[i]);
	}

	mergeSort(Lego, 1, n);
	for (int j = n; j > 1 && k < 0; j--)
	{
		for (int i = 1; i < j && k < 0; i++)
		k = bb(Lego,i,j-1,(tam * 10000000) - Lego[j]);
		ma = j;
	}
	if (k < 0)
	printf ("danger");
	else
		printf("yes %llu %llu",Lego[k], Lego[ma]);
	}
	else
	{
		printf("danger");
	}
}
	return 0;
}
