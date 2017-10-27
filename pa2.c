// Programming Assignment 2 
// Madeline Febinger and Sarah Almeda and Spencer ?
// Sarah edited this at 4PM on Thursday wow
// Sarah edited this again at 4:16PM

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
    
    /* Code for parsing input- Now functional!
     When each function is done, comment out the line that says printf("___ call goes here") thing and replace with actual function call
     -Sarah */
    
    char inStr[10]; //string that holds instruction
    char valStr[10]; //string that holds value
    int val; //integer that holds value
    
    while (scanf("%s", inStr) != EOF){ //gets next instruction
        
        if (strncmp(inStr, "INS", 3) == 0){
            scanf("%s", valStr);//gets value
            val = atoi(valStr);
            //insert(l, val);
            printf("Insert %i Call goes here\n", val);
        }
        else if (strncmp(inStr, "DEL", 3) == 0){
            fgets(valStr, 10, stdin);
            val = atoi(valStr);
            //delete(l, val);
            printf("Delete %i Call goes here\n", val);
        }
        else if (strncmp(inStr, "SEA", 3) == 0){
            fgets(valStr, 10, stdin);
            val = atoi(valStr);
            //search(*l, val);
            printf("Search %i Call goes here\n", val);
        }
        else if (strncmp(inStr, "MIN", 3) == 0){
            //getMinimum(l);
            printf("Min Call goes here\n");
        }
        else if (strncmp(inStr, "MAX", 3) == 0){
            //getMaximum(l);
            printf("Max Call goes here\n");
        }
        else if (strncmp(inStr, "PRE", 3) == 0){
            fgets(valStr, 10, stdin);
            val = atoi(valStr);
            //getPre(l, val);
            printf("PRE %i Call goes here\n", val);
        }
        else if (strncmp(inStr, "SUC", 3) == 0){
            fgets(valStr, 10, stdin);
            val = atoi(valStr);
            //getSuc(l, val);
            printf("SUC %i Call goes here\n", val);
        }
         else if (strncmp(inStr, "HEI", 3) == 0){
             //getHeight(l, val);
             printf("HEI Call goes here\n");
         }
        else{
            printf("INVALID INSTRUCTION");
        }
        
        
        
        
    }
    
	return 1;
}
