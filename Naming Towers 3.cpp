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

int check(nodo* tail, nodo* top)
{
	char temp1, temp2;
	while(tail != NULL && top != NULL)
	{
		temp1 = pop (&top);
		temp2 = Dequeue (&tail);
		if (temp1 != temp2)
			return 0;
	}
	return 1;
}


int main (void)
{
	int N, flag, cont;
	char ch;
	scanf ("%d", &N);
	fflush (stdin);
	for (int i = 1; i <= N; i++)
	{
		cont = 0;
		flag=1;
		nodo* tail = NULL, *top = NULL;
		scanf ("%c", &ch);
		while (ch != '\n')
		{
			cont++;
			if (!((ch >= 84 && ch <= 89) || ch == 65 || ch == 72 || ch == 73 || ch == 77 || ch == 79))
			{
				flag=0;
			}
			tail = Enqueue(tail, ch);
			top = push (top, ch);
			scanf ("%c", &ch);
		}
		if (flag == 0)
		{
			printf ("NO\n");
		}
		else
		{
			if(check(tail,top)==0)
				printf ("NO\n");
			else
				printf ("YES\n");
		}
	}
	return 0;
}
