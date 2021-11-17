#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXV 105
#define infinite 2147483647
#define NIL -1
#define FALSE 0
#define TRUE 1

typedef struct edg
{
	int vertex;
	struct edg *next;
}edge;

typedef struct
{
	edge *edges[MAXV + 1];
	int nvertex;
	int nedges;
} graph;

struct nodePQ
{
	int vertex;
	int distance;
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

int MinimumPQ(struct nodePQ A[])
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


void DecreaseKeyPQ(struct nodePQ A[], int i, int key, int positionVertex[])
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

void InsertPQ(struct nodePQ A[], int key, int vertex, int positionVertex[])
{
	heapSize++;
	A[heapSize].distance = infinite;
	A[heapSize].vertex = vertex;
	positionVertex[vertex] = heapSize;
	DecreaseKeyPQ(A, heapSize, key, positionVertex); 
}
void Dijkstra(int r, int phi[], int d[])
{
	int idVertex, u, v;
	struct nodePQ A[MAXV + 1];
	int positionVertex[MAXV + 1];
	int InPriorityQueue[MAXV + 1];
	edge *tempEdge;
	for (idVertex = 1; idVertex <= G.nvertex; idVertex++)
	{
		InPriorityQueue[idVertex] = TRUE;
	}
	
	for (idVertex = 1; idVertex <= G.nvertex; idVertex++)
	{
		phi[idVertex]=NIL;
		if (idVertex == r)
		{
			InsertPQ(A, 0, idVertex, positionVertex);
			d[idVertex] = 0;
		}
		else
		{
			InsertPQ(A, infinite, idVertex, positionVertex);
			d[idVertex] = infinite;
		}
	}
	while(heapSize >= 1)
	{
		u = ExtractMinPQ(A, positionVertex);
		InPriorityQueue[u] = FALSE;
		tempEdge = G.edges[u];
		while(tempEdge != NULL)
		{
		if (d[u] == infinite)
			break;
			v = tempEdge->vertex;
			if (d[v] > (d[u] + 1))
			{
				d[v] = d[u] + 1;
				phi[v] = u;
				DecreaseKeyPQ(A, positionVertex[v], d[v], positionVertex);
			}
			tempEdge = tempEdge->next;
		}
	}
}

void Solver(int s, int d, int idC)
{
	int d1[MAXV + 1], d2[MAXV + 1], phi[MAXV + 1], idVertex, result=0;	
	Dijkstra(s, phi, d1);
	Dijkstra(d, phi, d2);
	for (idVertex=1; idVertex <= G.nvertex; idVertex++)
	{
		if(d1[idVertex]+d2[idVertex]>result)
			result = d1[idVertex]+d2[idVertex];
	}
	printf("Case %d: %d\n", idC, result);
}

int main()
{
	int idCase, totalCases, n, m, u, v, s, d;
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
			newNode->vertex = v+1;
			newNode->next = G.edges[u+1];
			G.edges[u+1] = newNode;
			newNode = (edge*)malloc(sizeof(edge));
			newNode->vertex = u+1;
			newNode->next = G.edges[v+1];
			G.edges[v+1] = newNode;
		}
		scanf("%d %d", &s, &d);
		Solver(s+1,d+1, idCase);
		
	}
}
