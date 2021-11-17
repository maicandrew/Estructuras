#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define size 10005

int top = -1;
int queue[size];

void clean()
{
	for(int i=0; i<=top; i++)
	{
		queue[i] = 0;
	}
}

typedef struct node
{
	char key;
	struct node *next;
} nodo;

nodo* pushh(nodo* top, char n)
{
	nodo * newnode;
	newnode=(nodo*)malloc(sizeof (nodo));
	newnode->key=n;
	newnode->next=top;
	top=newnode;
	return top;
}

int StackEmpy(node *top)
{
	if(top==NULL)
		return 1;
	else
		return 0;
}

char popp (nodo ** top)
{
	char n= '3';
	nodo *temp;

	if (StackEmpy(*top)==0)
	{
		n=(*top)->key;
		temp=*top;
		*top=(*top)->next;
		free(temp);
	}
	return n;
}

nodo *Enqueue (nodo *tail, char element)
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

char Dequeue (nodo**tail)
{
	nodo *temp;
	char element='2';
	if((*tail)!=NULL)
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

int pripush(int pr)
{
	int i,j,k;
	if(top < size-1)
	{
		if(queue[top] < pr)
		{
			for(i=0; i<top; i++)
			{
				if(queue[i] < pr)

				{
					break;
				}
			}
			for(j=top; j>=i; j--)
			{
				queue[j+1] = queue[j];
			}
			top++;
			queue[i] = pr;
		}
		else
		{
			top++;
			queue[top] = pr;
		}
	}
}

int popri (void)
{
	int i, k;
	k = queue[0];
	for(i=0; i<top; i++)
	{
		queue[i] = queue[i+1];
	}
	queue[top] = 0;
	top--;
	return k;
}

int main (void)
{
	int n;
	int type, val;
	while (scanf ("%d", &n) != EOF)
	{
		nodo* tail = NULL, *topn = NULL;
		int top = -1;
		clean();
		int cola = 1, stack = 1, pri = 1, cont = 0, str;
		for(int i=1; i<=n; i++)
		{
			int temp1 = -1, temp2 = -1, temp3 = -1;
			scanf ("%d %d", &type, &val);
			if(type == 1)
			{
				tail = Enqueue(tail, val);
				topn = pushh (topn, val);
				pripush (val);
			}
			else
			{
				if (topn != NULL && tail != NULL)
				{
					temp1 = popp (&topn);
					temp2 = Dequeue (&tail);
					temp3 = popri();
				}
				if (temp1 != val)
				stack = 0;
				if (temp2 != val)
				cola = 0;
				if (temp3 != val)
				pri = 0;
			}
		}
		if (stack == 1)
		{
			str = 1;
			cont++;
		}
		if (cola == 1)
		{
			str = 2;
			cont++;
		}
		if (pri == 1)
		{
			str = 3;
			cont++;
		}
		if (cont == 0)
			printf ("impossible\n");
		else {
			if (cont >= 2)
			printf ("not sure\n");
			else {
				if (str == 1)
				printf ("stack\n");
				else {
					if (str == 2)
					printf ("queue\n");
					else printf ("priority queue\n");
				}
			}
		}
	}
	return 0;
}
