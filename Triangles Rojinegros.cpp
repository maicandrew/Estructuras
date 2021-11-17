#include <stdio.h>
#include <stdlib.h>
#define BLACK 0
#define RED 1
#define positiveInfinite 2147483647

typedef struct nodeTree
{
	struct nodeTree *p;
	struct nodeTree *left;
	struct nodeTree *right;
	int color;
	int key;
} nodo;

nodo* CreateNIL (nodo* X)
{
	nodo* NIL=(nodo*)malloc(sizeof(nodo));
	NIL->color=BLACK;
	NIL->left=NULL;
	NIL->right=NULL;
	NIL->key=positiveInfinite;
	NIL->p=X;
	return NIL;
}

nodo* TreeMinimum (nodo* x)
{
	while (x->left->key != positiveInfinite)
	{
		x = x->left;
	}
	return x;
}

nodo* TreeMaximum (nodo* x)
{
	while (x->right->key != positiveInfinite)
	{
		x = x->right;
	}
	return x;
}

nodo* TreeSuccessor (nodo* x)
{
	if (x->right->key != positiveInfinite)
		return TreeMinimum (x->right);
	nodo* y = x->p;
	while (y->key != positiveInfinite && x == y->right) {
		x = y;
		y = y->p;
	}
	return y;
}

nodo* TreePredecessor (nodo* x)
{
	if (x->left->key != positiveInfinite)
		return TreeMaximum (x->left);
	nodo *y = x->p;
	while (y->key != positiveInfinite && x == y->left) 
	{
		x = y;
		y = y->p;
	}
	return y;
}


nodo* LeftRotate (nodo* T, nodo* x)
{
	
	nodo *y=x->right;
	x->right=y->left;
	y->left->p=x;
	y->p=x->p;
	if (x->p->key==positiveInfinite)
		T=y;
	else
	{
		if (x==x->p->left)
			x->p->left=y;
		else
			x->p->right=y;
	}
	y->left=x;
	x->p=y;
	return T;
}

nodo* RightRotate (nodo* T, nodo* x)
{
	
	nodo *y=x->left;
	x->left=y->right;
	y->right->p=x;
	y->p=x->p;
	if (x->p->key==positiveInfinite)
		T=y;
	else
	{
		if (x==x->p->right)
			x->p->right=y;
		else
			x->p->left=y;
	}
	y->right=x;
	x->p=y;
	return T;
}

nodo* RB_InsertFixup (nodo* T, nodo* z)
{
	nodo*y;
	while (z->p->color == RED) 
	{
		if (z->p == z->p->p->left)
		{
			y = z->p->p->right;
			if (y->color == RED)
			{
				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			}
			else 
			{
				if (z == z->p->right)
				{
					z = z->p;
					T = LeftRotate (T, z);
				}
				z->p->color = BLACK;
				z->p->p->color = RED;
				T = RightRotate (T, z->p->p);
			}
		}
		else 
		{
			y = z->p->p->left;
			if (y->color == RED)
			{
				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			}
			else {
				if (z == z->p->left)
				{
					z = z->p;
					T = RightRotate (T, z);
				}
				z->p->color = BLACK;
				z->p->p->color = RED;
				T = LeftRotate (T, z->p->p);
			}
		}
	}
	T->color = BLACK;
	return T;
}
nodo* RB_TreeInsert (nodo* T, nodo* z)
{
	nodo* y = CreateNIL(NULL);
	nodo* x = T;
	nodo* pa;
	while (x->key != positiveInfinite) 
	{
		if (y->key==positiveInfinite)
			free(y);
		y = x;
		if (z->key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	z->p = y;
	if (y->key == positiveInfinite)
	{
		pa = T;
		T = z;
		free(pa);
	}
	else 
	{
		if (z->key < y->key)
		{
			free(y->left);
			y->left = z;
		}
		else
		{
			free(y->right);
			y->right = z;
		}
	}
	z->left=CreateNIL(z);
	z->right=CreateNIL(z);
	z->color=RED;
	
	T = RB_InsertFixup (T, z);
	return T;
}



nodo* RB_TreeDeleteFixup (nodo* T, nodo* x)
{
	nodo* w;
	while (x!=T && x->color==BLACK)
	{
		if (x==x->p->left)
		{
			w=x->p->right;
			if(w->color==RED)
			{
				w->color=BLACK;
				x->p->color=RED;
				T=LeftRotate(T,x->p);
				w=x->p->right;
			}
			if(w->left->color==BLACK && w->right->color==BLACK)
			{
				w->color=RED;
				x=x->p;
			}
			else
			{
				if(w->right->color==BLACK)
				{
					w->left->color=BLACK;
					w->color=RED;
					T=RightRotate(T,w);
					w=x->p->right;
				}
				w->color=x->p->color;
				x->p->color=BLACK;
				w->right->color=BLACK;
				T=LeftRotate(T,x->p);
				x=T;
			}
		}
		else
		{
			w=x->p->left;
			if(w->color==RED)
			{
				w->color=BLACK;
				x->p->color=RED;
				T=RightRotate(T,x->p);
				w=x->p->left;
			}
			if(w->right->color==BLACK && w->left->color==BLACK)
			{
				w->color=RED;
				x=x->p;
			}
			else
			{
				if(w->left->color==BLACK)
				{
					w->right->color=BLACK;
					w->color=RED;
					T=LeftRotate(T,w);
					w=x->p->left;
				}
				w->color=x->p->color;
				x->p->color=BLACK;
				w->left->color=BLACK;
				T=RightRotate(T,x->p);
				x=T;
			}
		}
	}
	x->color=BLACK;
	return T;
}

nodo* RB_TreeDelete (nodo* T, nodo* z)
{
	nodo* y, *x;
	if (z->left->key==positiveInfinite || z->right->key==positiveInfinite)
		y=z;
	else
		y=TreeSuccessor(z);
	if (y->left->key != positiveInfinite)
		x=y->left;
	else
		x=y->right;
	x->p=y->p;
	if (y->p->key==positiveInfinite)
		T=x;
	else
	{
		if (y=y->p->left)
			y->p->left=x;
		else
			y->p->right=x;
	}
	if (y!=z)
		z->key=y->key;
	if (y->color==BLACK)
		T=RB_TreeDeleteFixup(T, x);
	if (y==y->left->p)
		free(y->left);
	if (y==y->right->p)
		free(y->right);
	free(y);
	return T;
}

nodo* TreeSearch (nodo* x, int k)
{
	while (x->key != positiveInfinite && k != x->key) 
	{
		if (k < x->key)
		x = x->left;
		else 
		x = x->right;
	}
	return x;
}

void CleanMemory (nodo* T)
{
	nodo *x;
	while(T->key!=positiveInfinite)
	{
		x = TreeMinimum(T);
		T= RB_TreeDelete(T, x);
	}
	if (T->p->key==positiveInfinite)
		free(T->p);
	free(T);
}

int main ()
{
	int N;
	while (scanf ("%d", &N) != EOF) {
		nodo* T = CreateNIL (NULL);
		nodo *z, *y, *w;
		int x, ac = 0, cont = 0;
		for(int i = 1;i <= N; i++)
		{
			scanf("%d", &x);
			ac += x;
			z = (nodo*)malloc(sizeof(nodo));
			z->key = ac;
			T = RB_TreeInsert (T ,z);
		}
		if (ac % 3 == 0 && ac > 0)
		{
			int sal = ac / 3;
			while (T->key != positiveInfinite) {
				z = TreeMinimum (T);
				int temp = z->key;
				y = TreeSearch (T, temp+sal);
				w = TreeSearch (T, temp+sal+sal);
				if (y->key != positiveInfinite && w->key != positiveInfinite)
					cont++;
				T = RB_TreeDelete (T, z);
			}
			printf ("%d\n", cont);
		}
		else
		printf ("0\n");
	}
	return 0;
}
