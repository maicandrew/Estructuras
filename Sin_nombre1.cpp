#include <stdio.h>
#include <stdlib.h>
#include <math.h>


unsigned  int n,k,lims, liminf;
int x,y;

int main()
{

 while (scanf ("%d", &n) && n != 0)
 {
 fflush(stdin);
 
bool flag= false;
  for(int i = n; !flag; i++)
  {
   k = (unsigned  int) sqrt (((double)i) * 2);
   if (i == (k * (k+1))/2)
   {
    flag=true;
    lims=i;
   }
   else;
  }
  
  flag=false;

   for(int i = n-1; !flag; i--)
  {
   k = (unsigned  int) sqrt (((double)i) * 2);
   if (i == (k * (k+1))/2)
   {
    flag=true;
    liminf=i;
   }
   else;
  }
  
  
  
  y= n-liminf;
  x= lims-n+1;
   
  printf("%d ", x);
  printf("%d\n", y);
  fflush(stdin);
 }


 return 0;

}
