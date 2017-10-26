// Programming Assignment 2 
// Madeline Febinger and Sarah Almeda and Spencer ?
// Sarah edited this at 4PM on Thursday wow

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tree
{
	int key; 
	struct tree *parent; 
	struct tree *left;
	struct tree *right;
	int count;

} tree; 

tree *searchnode (tree *l, int x) // search returns a tree pointer
{
	
	if (l == NULL)
	{
		return (NULL);
	}

	if (l->key == x)
	{
		return l;
	}

	if (x < l->key)
	{
		return searchnode(l->left,x);
	}
	else
	{
		return searchnode(l->right,x);
	}
	return NULL;
}

int search (tree *t, int x) // search returns 1 if found, 0 if not found
{
	if (t == NULL)
	{
		return 0;
	}

	if (t->key == x)
	{
		return 1;
	}

	if (x < t->key)
	{
		return search(t->left,x);
	}
	else
	{
		return search(t->right,x);
	}
}

int insert(tree **l, int x)
{
	tree* newnode;
	
	if (*l == NULL) // inserting head node
	{
		newnode = malloc(sizeof(tree));
		newnode->key = x;
		newnode->left = newnode->right = newnode->parent = NULL;
		newnode->count = 1;
		*l = newnode;
		return x;
	}
	
	tree *a = malloc(sizeof(tree));

	if (search(*l,x) == 1)
	{
		a = searchnode(*l,x);

		a->count++;
	}
	else
	{
		newnode = malloc(sizeof(tree));
		newnode->key = x;
		newnode->left = newnode->right = newnode->parent = NULL;
		newnode->count = 1;

		int loop = 1;
		a = *l;
		while (loop)
		{
			if (x < a->key)
			{
				if (a->left == NULL)
				{
					a->left = newnode;
					newnode->parent = a;
					return x;

				}
				a = a->left;
			}
			else if (x > a->key)
			{
				if (a->right == NULL)
				{
					a->right = newnode;
					newnode->parent = a;
					return x;
					
				}
				a = a->right;
			}
		}
	}

	return 0;
} 

int delete(tree **l,int k)  // not finished, still need to add delete a node with 2 children which needs pred/succ
{

	tree* dnode = searchnode(*l,k);

	if (dnode == NULL)
	{
		return 0;
	}
	int numdeleted = dnode->count;

	if ( (dnode->left == NULL) && (dnode->right == NULL) ) // if deleting a node with no children 
	{
		tree *p = dnode->parent;
		if (p->left->key == dnode->key)
		{
			p->left = NULL;
		}
		else
		{
			p->right = NULL;
		}
		free(p);
		return numdeleted;
	}

	if (dnode->left == NULL) // if deleting a node with only a right child
	{
		tree* p = dnode->parent;
		tree* child = dnode->right;

		if (p->left == dnode)
		{
			p->left = child;
			child->parent = p;
		}
		else if (p->right == dnode)
		{
			p->right = child;
			child->parent = p;
		}	
		free(p);

		return numdeleted;	

	}

	if (dnode->right == NULL) // if deleting a node with only a left child
	{
		tree* p = dnode->parent;
		tree* child = dnode->left;

		if (p->left == dnode)
		{
			p->left = child;
			child->parent = p;
		}
		else if (p->right == dnode)
		{
			p->right = child;
			child->parent = p;
		}
		free(p);
		return numdeleted;		
	}	



}

void traverse(tree *l) // inorder traversal
{
		if (l == NULL)
		{
			return;
		}
		
		traverse(l->left);
		printf("%d ",l->key);
		traverse(l->right);	
	
	
}

int main()
{
	tree** l;
	insert(l,1);
	insert(l,5);
	insert(l,5);
	insert(l,6);

	printf("%d ", delete(l,5));
	
	traverse(*l);
	return 1;
}
