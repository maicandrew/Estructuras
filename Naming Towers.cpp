#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	char key;
	struct node *next;
} nodo;

nodo* push(nodo* top, char n)
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

char pop (nodo ** top)
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

int compara (nodo* tail, nodo* top)
{
	char temp1, temp2;
	while(tail != top && tail != top->next && top != tail->next)
	{
		temp1 = pop (&top);
		temp2 = Dequeue (&tail);
		if (temp1 != temp2 || temp1 > 90 || temp1 < 65 || temp2 > 90 || temp2 < 65)
			return 0;
	}
	return 1;
}

int main (void)
{
	int N;
	char car;
	scanf ("%d", &N);
	fflush (stdin);
	for (int i = 1; i <= N; i++)
	{
		int cp = 0, cont = 0;
		nodo* tail = NULL, *top = NULL;
		scanf ("%c", &car);
		while (car != 32 && car != '\n')
		{
			tail = Enqueue(tail, car);
			top = push (top, car);
			scanf ("%c", &car);
			cont++;
		}
		if (cont >= 1 && cont <= 100)
		cp = compara (tail, top);
		if (cp == 1)
			printf ("YES\n");
		else 
			printf ("NO\n");
	}
	return 0;
}
