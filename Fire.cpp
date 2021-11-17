#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int x;
    int y;
    int time;
} cell;

char maze[1002][1002];
cell Qf[1002*1002];
cell Qj[1002*1002];



int BSF(int posIX, int posIY, int alt, int anc)
{
//    int           V,x,x,y,y,
    int movX[5]= {0,-1,1,0,0};
    int movY[5]= {0,0,0,-1,1};

    int xj,yj,timej;
    int xf,yf,timef;

    int cabezaj=1,colaj=1,resul=-1;
    int cabezaf=1,colaf=1;


    Qj[colaj].x=posIX;
    Qj[colaj].y=posIY;
    Qj[colaj].time=1;
    maze[posIX][posIY]='j';
    colaj++;


    for(int s=1; s<=alt; s++)
    {
        for(int p=1; p<=anc; p++)
        {
            if(maze[s][p]=='F')
            {
                Qf[colaf].x=s;
                Qf[colaf].y=p;
                Qf[colaf].time=1;
                colaf++;
            }
        }

    }



    int gen=1;
    int flag=1;
    //Joe
    while(cabezaj<colaj)
    {


        while(Qf[cabezaf].time==gen && cabezaf<colaf)
        {
            xf=Qf[cabezaf].x;
            yf=Qf[cabezaf].y;
            timef=Qf[cabezaf].time;
            cabezaf++;


            for(int i=1; i<=4; i++)
            {
                if( (xf+movX[i]>=1) && (xf+movX[i]<=anc) && (yf+movY[i]>=1) && (yf+movY[i]<=alt) && ((maze[xf+movX[i]][yf+movY[i]] =='.' ) || (maze[xf+movX[i]][yf+movY[i]] =='j')))
                {
                    Qf[colaf].x=xf+movX[i];
                    Qf[colaf].y=yf+movY[i];
                    Qf[colaf].time=timef+1;
                    colaf++;
                    maze[xf+movX[i]][yf+movY[i]]='F';
                }

            }

        }
        gen=Qf[cabezaf].time;
        /*
        for(int s=1; s<=5; s++)
        {
            for(int p=1; p<=5; p++)
            {
                printf("%c", maze[p][s]);
            }
            printf("\n");
        }
        printf("\n");
        */

        while(Qj[cabezaj].time==flag)
        {
            xj=Qj[cabezaj].x;
            yj=Qj[cabezaj].y;
            timej=Qj[cabezaj].time;
            cabezaj++;

            for(int i=1; i<=4; i++)
            {
                if( (xj+movX[i]>=1) && (xj+movX[i]<=anc) && (yj+movY[i]>=1) && (yj+movY[i]<=alt) && (maze[xj+movX[i]][yj+movY[i]] =='.'))
                {
                    Qj[colaj].x=xj+movX[i];
                    Qj[colaj].y=yj+movY[i];
                    Qj[colaj].time=timej+1;
                    maze[xj+movX[i]][yj+movY[i]]='j';
                    colaj++;
                    

                    if(xj+movX[i] ==1 || xj+movX[i]==anc || yj+movY[i] ==1 || yj+movY[i]==alt )
                    {
                        resul=timej+1;
                        cabezaj=colaj;
                        break;
                    }
                }

            }
        }
        flag=Qj[cabezaj].time;
        /*
        for(int s=1; s<=5; s++)
        {
            for(int p=1; p<=5; p++)
            {
                printf("%c", maze[p][s]);
            }
            printf("\n");
        }
        printf("\n");
        */



    }

    return resul;
}


int main()
{

    int R,C,V;
    int ijx,ijy,ifx,ify;

    char fila[1002];


    scanf("%d",&V);
    while(V!=0)
    {
        scanf("%d %d",&R,&C);
        for(int r=1; r<=R; r++)
        {
            scanf("%s",&fila);
            for(int c=1; c<=C; c++)
            {
                maze[c] [r]=fila[c-1];
                if (maze[c] [r] =='J')
                {
                    ijx=c;
                    ijy=r;
                }
            }

        }
        int joe;


        if(ijx==1 || ijy==1 ||ijx==C || ijy==R )
        {
            printf("1\n");
        }
        else
        {
            joe = BSF(ijx, ijy, R, C);

            if(joe==-1)
            {
                puts("IMPOSSIBLE");
            }
            else
            {
                printf("%d\n", joe);
            }
        }
        Qf->time = {0};
        Qj->time = {0};


        V--;
    }
    return 0;

}
