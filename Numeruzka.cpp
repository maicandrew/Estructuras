#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int n,k,lims=0, liminf=0, ini;

int main (void)
{

 while (scanf ("%llu", &n) && n != 0)
 {

  k = (int) sqrt (((double)n) * 2);
  ini = (k * (k+1))/2;
  int lol=(1+sqrt(8*ini))/2;

  if (ini>=n)
  {
   lims=ini;
   liminf = ((lol-1) * ((lol-1)+1))/2;
  }
  else
  {
   liminf=ini;
   lims = ((lol+1) * ((lol+1)+1))/2;
   
  }

  if((lims-liminf)%2!=0)
  {
   printf("%d\n", lol);
  }
  else
  {
   printf("%d\n", lol-1);
  }




 }


 return 0;

}
