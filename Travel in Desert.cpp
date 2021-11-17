#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAXV 105
#define infinite 2147483647
#define NIL -1
#define FALSE 0
#define TRUE 1
int phip[MAXV +1];
double dp[MAXV +1];

int phid[MAXV +1];
double dd[MAXV +1];

typedef struct edg
{
	int vertex;
	double dis;
	double temp;
	struct edg *next;
} edge;

typedef struct
{
	edge *edges[MAXV + 1];
	int nvertex;
	int nedges;
} graph;

struct nodePQ
{
	int vertex;
	double distance;
};
graph G;

int heapSize =0;
int left(int i)
{
	return 2*i;
}

int right(int i)
{
	return 2*i + 1;
}
int parent(int i)
{
	return i/2;
}

void MinHeapifyPQ(struct nodePQ A[], int i, int positionVertex[])
{
	int l, r, little, posicionTemp;
	l=left(i);
	r=right(i);
	struct nodePQ nodeTemp;
	if((l<= heapSize) && (A[l].distance < A[i].distance) )
		little =l;
	else
		little =i;
	if ((r<=heapSize) && (A[r].distance < A[little].distance))
		little=r;
	if (little != i)
	{
		nodeTemp = A[i];
		posicionTemp= positionVertex[A[i].vertex];
		positionVertex[A[i].vertex] = positionVertex[A[little].vertex];
		A[i]=A[little];
		positionVertex[A[little].vertex] = posicionTemp;
		A[little] = nodeTemp;

		MinHeapifyPQ(A, little,positionVertex);
	}
}


double MinimumPQ(struct nodePQ A[])
{
	return A[1].distance;
}


int ExtractMinPQ(struct nodePQ A[], int positionVertex[])
{
	int min =0;
	struct nodePQ nodeTemp;
	if (heapSize >= 1)
	{
		min = A[1].vertex;
		nodeTemp = A[1];

		A[1] = A[heapSize];
		positionVertex[A[heapSize].vertex] = 1;

		A[heapSize] = nodeTemp;
		positionVertex[A[heapSize].vertex] = heapSize;
		heapSize--;
		MinHeapifyPQ(A, 1, positionVertex);
	}
	return min;
}


void DecreaseKeyPQ(struct nodePQ A[], int i, double key, int positionVertex[])
{
	int positionTemp;
	struct nodePQ nodeTemp;
	if (key<A[i].distance)
	{
		A[i].distance = key;
		while ((i>1) && (A[parent(i)].distance > A[i].distance))
		{
			nodeTemp = A[i];
			positionTemp = positionVertex[A[i].vertex];
			positionVertex[A[i].vertex] = positionVertex[A[parent(i)].vertex];
			A[i]=A[parent(i)];

			positionVertex[A[parent(i)].vertex] = positionTemp;
			A[parent(i)] = nodeTemp;
			i = parent (i);

		}
	}
}


void InsertPQ(struct nodePQ A[], double key, int vertex, int positionVertex[])
{
	heapSize++;
	A[heapSize].distance = infinite;
	A[heapSize].vertex = vertex;
	positionVertex[vertex] = heapSize;
	DecreaseKeyPQ(A, heapSize, key, positionVertex);
}


void Prim(int r)
{
	int idVertex, u, v;
	double temp;
	struct nodePQ A[MAXV + 1];
	int positionVertex[MAXV + 1];
	double InPriorityQueue[MAXV + 1];
	edge *tempEdge;
	for (idVertex = 1; idVertex <= G.nvertex; idVertex++)
	{
		InPriorityQueue[idVertex] = TRUE;
	}

	for (idVertex = 1; idVertex <= G.nvertex; idVertex++)
	{
		phip[idVertex]=NIL;
		if (idVertex == r)
		{
			InsertPQ(A, 0, idVertex, positionVertex);
			dp[idVertex] = 0;
		}
		else
		{
			InsertPQ(A, infinite, idVertex, positionVertex);
			dp[idVertex] = infinite;
		}
	}
	while(heapSize >= 1)
	{
		u = ExtractMinPQ(A, positionVertex);
		InPriorityQueue[u] = FALSE;
		tempEdge = G.edges[u];
		while(tempEdge != NULL)
		{
			if (dp[u] == infinite)
				break;
			v = tempEdge->vertex;
			temp = tempEdge->temp;
			if ((InPriorityQueue[v] == TRUE) && (temp < dp[v]))
			{
				phip[v] = u;
				dp[v] = temp;
				DecreaseKeyPQ(A, positionVertex[v], dp[v], positionVertex);
			}
			tempEdge = tempEdge->next;
		}
	}
}

void Dijkstra(int r, double temp)
{
	int idVertex, u, v;
	double dis,newtemp;
	struct nodePQ A[MAXV + 1];
	int positionVertex[MAXV + 1];
	edge *tempEdge;

	for (idVertex = 1; idVertex <= G.nvertex; idVertex++)
	{
		phid[idVertex]=NIL;
		if (idVertex == r)
		{
			InsertPQ(A, 0, idVertex, positionVertex);
			dd[idVertex] = 0;
		}
		else
		{
			InsertPQ(A, infinite, idVertex, positionVertex);
			dd[idVertex] = infinite;
		}
	}
	while(heapSize >= 1)
	{
		u = ExtractMinPQ(A, positionVertex);
		tempEdge = G.edges[u];
		while(tempEdge != NULL)
		{
            if (dd[u] == infinite)
                break;
			v = tempEdge->vertex;
			dis = tempEdge->dis;
			newtemp= tempEdge->temp;
			if ( newtemp <=temp && (dd[v] > (dd[u] + dis)))
			{
				dd[v] = dd[u] + dis;
				phid[v] = u;
				DecreaseKeyPQ(A, positionVertex[v], dd[v], positionVertex);
			}
			tempEdge = tempEdge->next;
		}
	}
}


void printGraph()
{
	int idVertex;
	edge *actualNode;
	for (idVertex=1; idVertex<=G.nvertex; idVertex++)
	{
		printf("[Vertex: %d] ", idVertex);
		actualNode = G.edges[idVertex];
		while(actualNode != NULL)
		{
			printf("-> (%d, %.1lf, %.1lf) ", actualNode->vertex, actualNode->temp, actualNode->dis);
			actualNode = actualNode->next;
		}
		printf("-> NULL\n");
	}
	return;
}



void CleanMemory ()
{

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









void solver(int I, int F)
{
	double caliente=0;
	double dis = 0;
	heapSize =0;
	Prim(I);
	
	
	int paso = F;
	while(paso!=NIL)
	{
		if(dp[paso]>caliente)
		{
		
			caliente=dp[paso];
		}
		paso=phip[paso];
	}
	

	heapSize =0;
	Dijkstra(F,caliente);

	int val = I;
	printf("%d", val);
	caliente = dp[val];
	dis = dd[val];
	val = phid[val];
	while(val != NIL)
	{
		printf(" %d", val);
		if (dp[val] > caliente)
            caliente = dp[val];
		dis += dd[val];
		val = phid[val];
	}
	printf("\n");
	printf("%.1lf %.1lf\n", dd[I], caliente);
}



int main()
{
	int N, E, u, v,S,T;
	double temp, dis;
	int idEdge, idVertex;
	edge *newNode, *actualNode;

	while(scanf("%d %d", &N, &E)!=EOF)
	{
		scanf("%d %d", &S, &T);
		G.nvertex = N;
		G.nedges = E;

		for (idEdge=1; idEdge<=E; idEdge ++)
		{
			scanf("%d %d %lf %lf", &u, &v, &temp ,&dis);
			newNode = (edge*)malloc(sizeof(edge));
			newNode->vertex = v;
			newNode->temp = temp;
			newNode->dis = dis;
			newNode->next = G.edges[u];
			G.edges[u] = newNode;
			newNode = (edge*)malloc(sizeof(edge));
			newNode->vertex = u;
			newNode->temp = temp;
			newNode->dis = dis;
			newNode->next = G.edges[v];
			G.edges[v] = newNode;
		}
		
		solver(S,T);
		CleanMemory ();
	}

}
