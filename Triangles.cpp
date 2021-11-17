#include <stdio.h>
#include <math.h>  
int puntos[100005];
int sumpun[100005];

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

	int n;
	sumpun[0]=0;
	puntos[0]=0;
	while (scanf ("%d", &n) !=EOF)
	{
		int con=0;
		if(n!=0)
			for(int i=1; i<=n; i++)
			{
				scanf("%d", &puntos[i]);
				sumpun[i] =puntos[i];
			}

		for(int i=2; i<=n; i++)
		{
			sumpun[i]+=sumpun[i-1];
		}

		int tot=sumpun[n];
		
		
		
		if(tot%3 == 0)
		{
			int sal=tot/3;
			for(int i=0 ,x=0; i<=n; i++)
			{
				x=sumpun[i];
				int k = bb(sumpun,0,n, (x+sal)%tot);
				int j = bb(sumpun,0,n, (x+sal+sal)%tot);

				if (k>0 && j >0)
					con++;
			}

			printf("%d\n",  con/3);

		}
		else
		puts("0\n");

	}

}
