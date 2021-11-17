#include <stdio.h>
#include <stdlib.h>

#define MyInf 2147483647
typedef struct node
{
	int key;
	struct node *next;
}nodo;

nodo *Enqueue (nodo *tail, int element)
{
	nodo *NewNode;
	NewNode = (nodo *)malloc(sizeof (nodo));
	NewNode->key = element;
	if (tail==NULL)
	{
		NewNode->next=NewNode;
		tail=NewNode;
	}
	else
	{
		NewNode->next=tail->next;
		tail->next=NewNode;
		tail=NewNode;
	}
	return tail;
}

int Dequeue (nodo**tail)
{
	nodo *temp;
	int element=MyInf;
	if((*tail)==NULL)
		printf ("Empty queue\n");
	else
	{
		if ((*tail)->next==(*tail))
		{
			element=(*tail)->key;
			temp=(*tail);
			free(temp);
			(*tail)=NULL;
		}
		else
		{
			temp=(*tail)->next;
			(*tail)->next=temp->next;
			element = temp->key;
			free(temp);
		}
	}
	return element;
}
int main()
{
	nodo *tail=NULL;
	int element, TypeOperation;
	while(scanf("%d", &TypeOperation)!= EOF)
	{
		if (TypeOperation == 1)
		{
			scanf ("%d", &element);
			tail = Enqueue(tail, element);
		}
		else if (TypeOperation == 2)
		{
			element = Dequeue (&tail);
			if (element!=MyInf)
				printf ("%d", element);
		}
	}
	return 0;
}
