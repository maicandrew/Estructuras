#include <stdio.h>
#include <stdlib.h>
#include <math.h>


unsigned long long int n,k,lims=0, liminf=0;
unsigned long long int ini;

int main()
{

 while (scanf ("%llu", &n) && n != 0)
 {

  k = (unsigned long long int) sqrt (((double)n) * 2);
  ini = (k * (k+1))/2;
  unsigned long long int lol=(1+sqrt(8*ini))/2;

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
   printf("%d ", lims-n+1);
   printf("%d\n", n-liminf);
  }
  else
  {
   printf("%d ", n-liminf);
   printf("%d\n", lims-n+1);
  }




 }


 return 0;

}
