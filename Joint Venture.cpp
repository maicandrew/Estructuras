#include <stdio.h>
#include <stdlib.h>


typedef struct nodeTree {
	struct nodeTree *p;
	struct nodeTree *left;
	struct nodeTree *right;
	int key;
} nodo;

nodo* TreeMinimum (nodo* x)
{
	while (x->left != NULL)
	{
		x = x->left;
	}
	return x;
}

nodo* TreeMaximum (nodo* x)
{
	while (x->right != NULL)
	{
		x = x->right;
	}
	return x;
}

nodo* TreeSuccessor (nodo* x)
{
	if (x->right != NULL)
	return TreeMinimum (x->right);
	nodo* y = x->p;
	while (y != NULL && x == y->right) {
		x = y;
		y = y->p;
	}
	return y;
}

nodo* TreeInsert (nodo* T, nodo* z)
{
	nodo* y = NULL;
	nodo* x = T;
	while (x != NULL) {
		y = x;
		if (z->key < x->key)
		x = x->left;
		else
		x = x->right;
	}
	z->p = y;
	if (y == NULL)
	T = z;
	else {
		if (z->key < y->key)
		y->left = z;
		else
		y->right = z;
	}
	return T;
}

void InOrderTreeWalk (nodo* x)
{
	if (x != NULL)
	{
		InOrderTreeWalk (x->left);
		printf ("%d ", x->key);
		InOrderTreeWalk (x->right);
	}
}

nodo* TreeSearch (nodo* x, int k)
{
	while (x != NULL && k != x->key) {
		if (k < x->key)
		x = x->left;
		else 
		x = x->right;
	}
	return x;
}

nodo* TreePredecessor (nodo* x)
{
	if (x->left != NULL)
		return TreeMaximum (x->left);
	nodo *y = x->p;
	while (y != NULL && x == y->left) {
		x = y;
		y = y->p;
	}
	return y;
}

nodo* TreeDelete (nodo* T, nodo* z)
{
	nodo *x, *y;
	if (z->left == NULL || z->right == NULL)
		y = z;
	else 
		y = TreeSuccessor(z);
	if (y->left != NULL)
		x = y->left;
	else
		x = y->right;
	if (x != NULL)
		x->p = y->p;
	if (y->p == NULL)
		T = x;
	else {
		if (y == y->p->left)
			y->p->left = x;
		else 
			y->p->right = x;
	}
	if (y != z)
	z->key = y->key;
	free(y);
	return T;
}

int main (void) {
	int ma, me;
	int tam, n;
	long long unsigned int val;
	while (scanf ("%d", &tam) != EOF && tam >= 1) {
		nodo *T = NULL, *z = NULL, *w = NULL;
		scanf("%d", &n);
		if(n != 0)
		{
			for(int i = 1; i <= n; i++) {
			 	scanf("%llu", &val);
				z = (nodo*) malloc (sizeof(nodo));
				z->left = NULL;
				z->right = NULL;
				z->key = val;
				T = TreeInsert (T, z);
			}
			while (T != NULL){
				z = TreeMinimum(T);
				w = TreeSearch (T, (tam*10000000) - z->key);
				if (w != NULL)
				{
					me = z->key;
					ma = w->key;
					break;
				}
				else T = TreeDelete (T, z);
			}
			if (z == NULL || w == NULL)
				printf ("danger\n");
			else
				printf("yes %llu %llu\n",me, ma);
		}
		else
		{
			printf("danger\n");
		}
	}
}
