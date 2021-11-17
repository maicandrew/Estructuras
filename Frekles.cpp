#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 
#define MAXV 105
#define infinite 2147483647
#define NIL -1
#define FALSE 0
#define TRUE 1


typedef struct edg
{
	int vertex;
	double weight;
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


double ExtractMinPQ(struct nodePQ A[], int positionVertex[])
{
	double min =0;
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
	double positionTemp;
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


void Prim(double r, double phi[], double d[])
{
	int idVertex, u, v;
	double weight;
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


void Solver()
{
	double d[MAXV + 1], phi[MAXV + 1];
	int idVertex;
	double result=0;
	Prim(1, phi, d);
	for (idVertex=1; idVertex <= G.nvertex; idVertex++)
	{
		result += d[idVertex];
	}
	printf("%.2lf\n", result);
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
			printf("-> (%d, %lf) ", actualNode->vertex, actualNode->weight);
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




double Vx[105];
double Vy[105];

int main()
{
	double x,y;
	int idCase, totalCases, n, m;
	int idEdge, idVertex;
	edge *newNode, *actualNode;
	scanf ("%d", &totalCases);
	for (idCase=1; idCase<=totalCases; idCase++)
	{
		scanf("%d", &n);
		G.nvertex = n;
		G.nedges = ((n-1)*n)/2;
		
		
		for (idEdge=1; idEdge<=n; idEdge++)
		{
			scanf("%lf %lf", &x, &y);
			Vx[idEdge]=x;
			Vy[idEdge]=y;
		}
		
		for (idEdge=1; idEdge<=n; idEdge ++)
		{
			for(int i=1;i<=n;i++)
			{
				double dis = sqrt((pow( Vx[idEdge]-Vx[i] ,2)) +  (pow( Vy[idEdge]-Vy[i] ,2)));
				newNode = (edge*)malloc(sizeof(edge));
				newNode->vertex = i;
				newNode->weight = dis;
				newNode->next = G.edges[idEdge];
				G.edges[idEdge] = newNode;
			}
		}
		
		
		Solver();
		if (idCase<totalCases)
		printf("\n");
		CleanMemory ();
		
	}
}
