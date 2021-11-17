#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXV 200000
#define infinite 2147483647
#define NIL -1
#define FALSE 0
#define TRUE 1


long long int positionVertex[MAXV + 1];
long long int InPriorityQueue[MAXV + 1];
long long int d[MAXV + 1], phi[MAXV + 1], idVertex, result=0;



typedef struct edg
{
	int vertex;
	long long weight;
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
	long long int distance;
};

struct nodePQ A[MAXV + 1];

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

void MinHeapifyPQ(struct nodePQ A[], int i, long long int  positionVertex[])
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

long long int MinimumPQ(struct nodePQ A[])
{
	return A[1].distance;
}

long long int ExtractMinPQ(struct nodePQ A[], long long int  positionVertex[])
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


long long int DecreaseKeyPQ(struct nodePQ A[], int i, long long int key, long long int  positionVertex[])
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

void InsertPQ(struct nodePQ A[], long long int key, long long int  vertex, long long int  positionVertex[])
{
	heapSize++;
	A[heapSize].distance = infinite;
	A[heapSize].vertex = vertex;
	positionVertex[vertex] = heapSize;
	DecreaseKeyPQ(A, heapSize, key, positionVertex);
}
void Prim(int r, long long int phi[], long long int d[])
{
	long long int idVertex, u, v, weight;
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
			weight = tempEdge->weight;
			if ((InPriorityQueue[v] == TRUE) && (weight < d[v]))
			{
				phi[v] = u;
				d[v] = weight;
				DecreaseKeyPQ(A, positionVertex[v], d[v], positionVertex);
			}
			tempEdge = tempEdge->next;
		}
	}
}

void Solver(int n)
{
	result=0;
	Prim(1, phi, d);
	for (idVertex=1; idVertex <= G.nvertex; idVertex++)
	{
		result += d[idVertex];
	}
	printf("%lli\n", n- result);
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
			printf("-> (%d, %d) ", actualNode->vertex, actualNode->weight);
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


int main()
{
	int idCase, totalCases, n, m, u, v, w;
	int idEdge, idVertex;
	edge *newNode, *actualNode;
	scanf("%d %d", &m, &n);
	while(n!=0 && m!=0)
	{
		G.nvertex = m;
		G.nedges = n;
		long long int total=0;
		
		
		for (idEdge=1; idEdge<=n; idEdge ++)
		{
			scanf("%d %d %d", &u, &v, &w);
			u++;
			v++;
			total=total+w;
			newNode = (edge*)malloc(sizeof(edge));
			newNode->vertex = v;
			newNode->weight = w;
			newNode->next = G.edges[u];
			G.edges[u] = newNode;
			newNode = (edge*)malloc(sizeof(edge));
			newNode->vertex = u;
			newNode->weight = w;
			newNode->next = G.edges[v];
			G.edges[v] = newNode;
		}
		Solver(total);
		scanf("%d %d", &m, &n);
		CleanMemory ();
	}

}
