#include <stdio.h>
#include <math.h>

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
	int captank[50005], n, q, k, i, j, w;
	scanf ("%d", &n);
	for (i = 1; i <= n; i++) {
    scanf("%d",&captank[i]);
	}
	scanf ("%d", &q);
	for(i=1;i<=q;i++) {
    	scanf("%d",&k);
    	j=bb(captank,1,n,k);
	   if(j < 0)
    {
    	j *= -1;
		if (captank[j] == k)
    	{
    		printf ("%d ", captank[j]);
    		if (j+1 <= n)
    		printf ("%d", captank[j+1]);
    		else printf ("X");
		}
		else {
			printf ("%d ", captank[j]);
    		if (j+1 <= n)
    		printf ("%d", captank[j+1]);
    		else printf ("X");
		}	
	}
	else {
    	for (w = j; w >= 1 && captank[w] == k; w--);
    	if (w >= 1)
    		printf ("%d ", captank[w]);
    	else printf ("X ");
    	for (w = j; w <= n && captank[w] == k; w++);
    	if (w <= n)
    		printf ("%d", captank[w]);
    	else printf ("X");
    }
    printf ("\n");
    
  }
  
  return 0;
 
}
