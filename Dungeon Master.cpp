#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	int x;
	int y;
	int z;
	int time;
} cell;

char maze[32][32][32];

int BSF(int posIX, int posIY, int posIZ, int alt, int anc, int cap)
{
//	int           V,x,x,y,y,z,z
	int movX[7]= {0,-1,1,0,0,0,0};
	int movY[7]= {0,0,0,-1,1,0,0};
	int movZ[7]= {0,0,0,0,0,-1,1};

	int x,y,z,time;

	int cabeza=1,cola=1,resul=-1;

	cell Q[32768];

	Q[cola].x=posIX;
	Q[cola].y=posIY;
	Q[cola].z=posIZ;
	Q[cola].time=0;
	maze[posIX][posIY][posIZ]='#';
	cola++;

	while(cabeza<cola)
	{
		x=Q[cabeza].x;
		y=Q[cabeza].y;
		z=Q[cabeza].z;
		time=Q[cabeza].time;
		cabeza++;

		for(int i=1; i<=6; i++)
		{
			if( (x+movX[i]>=1) && (x+movX[i]<=anc) && (y+movY[i]>=1) && (y+movY[i]<=alt) && (z+movZ[i]>=1) && (z+movZ[i]<=cap) && (maze[x+movX[i]][y+movY[i]][z+movZ[i]] =='.'))
			{
				Q[cola].x=x+movX[i];
				Q[cola].y=y+movY[i];
				Q[cola].z=z+movZ[i];
				Q[cola].time=time+1;
				cola++;
			}

			if(maze[x+movX[i]][y+movY[i]][z+movZ[i]] =='E')
			{
				resul=time+1;
				cabeza=cola;
				break;
			}
			else
			{
				maze[x+movX[i]][y+movY[i]][z+movZ[i]] ='#';
			}

		}

	}

	return resul;
}


int main()
{

	int L,R,C;
	int ix,iy,iz;

	char fila[32];

	scanf("%d %d %d",&L,&C,&R);

	while(L!=0 && R!=0 && C!=0)
	{
		for(int l=1; l<=L; l++)
		{
			for(int c=1; c<=C; c++)
			{
				scanf("%s",fila);
				for(int r=1; r<=R; r++)
				{
					maze[r] [c] [l]=fila[r-1];
					if (maze[r] [c] [l]=='S')
					{
						ix=r;
						iy=c;
						iz=l;
					}
				}
			}
		}

		int val = BSF(ix, iy, iz, C, R, L);

		if(val==-1)
		{
			printf("Trapped!\n");
		}
		else
		{
			printf("Escaped in %d minute(s).\n", val);
		}
		
		scanf("%d %d %d",&L,&C,&R);
		
	}
	return 0;
	
}
