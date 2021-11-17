#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXV 100005
#define infinite 2147483647
#define NIL -1
#define WHITE 1
#define BLACK 2
#define GRAY 3

typedef struct edg
{
	int vertex;
	struct edg *next;
} edge;

typedef struct
{
	edge *edges[MAXV + 1];
	int nvertex;
	int nedges;
} graph;

graph G;

int time=0;

int phi[10005], color[10005], fin[10005], des[10005];
int pila[10005];
int toppila=1;
int cont=0;


void DFS_visit(int u)
{
	int v;
	edge *tempEdge;
	color[u]=GRAY;
	time++;
	des[u]=time;

	tempEdge=G.edges[u];
	while(tempEdge!=NULL)
	{
		v=tempEdge->vertex;
		if(color[v]==WHITE)
		{
			phi[v]=u;
			DFS_visit(v);
		}
		tempEdge=tempEdge->next;
	}
	color[u]=BLACK;
	time++,
	     fin[u]=time;
	pila[toppila]=u;
	toppila++;

}

void DFS()
{
	int u;
	for(u=1; u<=G.nvertex; u++)
	{
		color[u]=WHITE;
		phi[u]=NIL;
		des[u]=0;
		fin[u]=0;
	}
	time=0;
	for(u=1; u<=G.nvertex; u++)
	{
		if(color[u]==WHITE)
		{
			DFS_visit(u);
		}
	}

}


void DFS_visit2(int u)
{
	int v;
	edge *tempEdge;
	color[u]=GRAY;
	time++;
	des[u]=time;

	tempEdge=G.edges[u];
	while(tempEdge!=NULL)
	{
		v=tempEdge->vertex;
		if(color[v]==WHITE)
		{
			phi[v]=u;
			DFS_visit(v);
		}
		tempEdge=tempEdge->next;
	}
	color[u]=BLACK;
	time++,
	     fin[u]=time;

}

int DFS2()
{
	int u;
	for(u=1; u<=G.nvertex; u++)
	{
		color[u]=WHITE;
		phi[u]=NIL;
		fin[u]=0;
		des[u]=0;
	}
	time=0;
	for(int f=toppila; f>=1; f--)
	{
		if(color[pila[f]]==WHITE)
		{
			DFS_visit2(pila[f]);
			cont++;
		}
	}
	return cont;

}




void CleanMemory ()
{
	toppila=1;
	cont=0;
	int idVertex, idEdge;
	edge *nodeLeft, *nodeRight;
	for (idVertex=1; idVertex<=G.nvertex; idVertex ++)
	{

		nodeLeft = G.edges[idVertex];
		while(nodeLeft != NULL)
		{
			nodeRight = nodeLeft->next;
			free(nodeLeft);
			nodeLeft = nodeRight;

		}
		G.edges[idVertex] = NULL;
	}


}



int main()
{

	int idCase, totalCases, n, m, u, v;
	int idEdge, idVertex;
	edge *newNode, *actualNode;
	scanf ("%d", &totalCases);
	for (idCase=1; idCase<=totalCases; idCase++)
	{
		scanf("%d %d", &n, &m);
		G.nvertex = n;
		G.nedges = m;
		for (idVertex=1; idVertex<=n; idVertex++)
		{
			G.edges[idVertex] = NULL;
		}
		for (idEdge=1; idEdge<=m; idEdge ++)
		{
			scanf("%d %d", &u, &v);
			newNode = (edge*)malloc(sizeof(edge));
			newNode->vertex = v;
			newNode->next = G.edges[u];
			G.edges[u] = newNode;
		}

		DFS();
		int val=DFS2();
		printf("Case %d: %d\n", idCase,val);

		for(int z=1; z<=10005;z++)
		{
			pila[z]=0;
		}

		CleanMemory ();
	}

	return 0;

}
