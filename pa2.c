// Programming Assignment 2 
// Madeline Febinger and Sarah Almeda and Spencer ?


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
		if (dnode->parent != NULL)
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
			free(dnode);
			return numdeleted;
		}
		else
		{
			*l = NULL;
			return numdeleted;
		}


	}

	if (dnode->left == NULL) // if deleting a node with only a right child
	{
			tree* p = dnode->parent;
			tree* child = dnode->right;

			if (p != NULL)
			{
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
			
			}
			else
			{
				*l = child;
				child->parent = NULL; 
			}
			free(dnode);
			return numdeleted;

	}

	if (dnode->right == NULL) // if deleting a node with only a left child
	{
		tree* p = dnode->parent;
		tree* child = dnode->left;

			if (p != NULL)
			{
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
						
			}
			else
			{
				*l = child;
				child->parent = NULL; 
				
			}
			free(dnode);
			return numdeleted;		
	}

	else // deleting a node with 2 children 
	{
		int m = getMinimum(dnode->right);
		tree* min = searchnode(*l,m);

		dnode->key = min->key;
		dnode->count = min->count;

		tree* p = min->parent;
		tree* child = min->right; 

		p->right = child;
		if (child != NULL)
		{
			child->parent = p;
		}
		

		free(min);
		return numdeleted;
	}
    
    return 0;

}

void traverse(tree *l) // inorder traversal
{
		if (l == NULL)
		{
			return;
		}
		printf("%d:\n ",l->key);
        printf("TO THE LEFT OF %d:\n ",l->key); //Use this and the printf statement below to print out the tree for testing purposes
		traverse(l->left);
        printf("TO THE RIGHT OF %d:\n ",l->key);
		traverse(l->right);	
	
	
}
int getMinimum (tree *l)
{
    if (l->left == NULL)
    {
        return l->key;
    }

    return getMinimum(l->left);
}
int getMaximum (tree *l)
{
    if (l->right == NULL)
    {
        return l->key;
    }
    
    return getMaximum(l->right);
}

int getPre(tree *l,int k)
{
	tree* a = searchnode(l,k);

	if (a == NULL) // return -1 if there is no node with this key
	{
		return -1; 
	}

	if (a->left != NULL)
	{
		a = a->left;

		while (a->right != NULL)
		{
			a = a->right;
		}
		return a->key;
	}

	tree* p = a->parent;

	if (p->right == a)
	{
		return p->key;
	}

	if (p->left == a)
	{
		while (a == p->left) 
		{
			a = p;
			if (p->parent == NULL)
			{
				return -1;
			}
			p = p->parent;
		}
		return p->key;
		
	}

	return -1;
}

int getSuc(tree *l,int k)
{
	tree* a = searchnode(l,k);

	if (a == NULL) // return -1 if there is no node with this key
	{
		return -1; 
	}

	if (a->right != NULL)
	{
		a = a->right;

		while (a->left != NULL)
		{
			a = a->left;
		}
		return a->key;
	}

	tree* p = a->parent;

	if (p->left == a)
	{
		return p->key;
	}

	if (p->right == a)
	{
		while (a == p->right) 
		{
			a = p;
			if (p->parent == NULL)
			{
				return -1;
			}
			p = p->parent;
		}
		return p->key;
		
	}	

	return -1;
}

int getHeight(tree *l) // inorder traversal
{
    if (l == NULL)
    {
        return -1;
    }
    if ((getHeight(l->left) + 1) > (getHeight(l->right) + 1)){
        return (getHeight(l->left)+1);
    }
    else{
        return (getHeight(l->right)+1);
    }
    
    
}

int main()
{
    
	tree * t; //I had to do this to get it to work on my computer
    tree ** l;
    l = &t; //this too
    
	//printf("%d\n", insert(l,1));
	//printf("%d\n", insert(l,5));

	//printf("%d ", delete(l,5));
	
	
    
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
            printf("%i\n", insert(l, val));
        }
        else if (strncmp(inStr, "DEL", 3) == 0){
            fgets(valStr, 10, stdin);
            val = atoi(valStr);
            //delete(l, val);
            printf("%i\n", delete(l,val));
        }
        else if (strncmp(inStr, "SEA", 3) == 0){
            fgets(valStr, 10, stdin);
            val = atoi(valStr);
            
            printf("%i\n", search(*l, val));
        }
        else if (strncmp(inStr, "MIN", 3) == 0){
            printf("%i\n", getMinimum(*l));
        }
        else if (strncmp(inStr, "MAX", 3) == 0){
            printf("%i\n", getMaximum(*l));
        }
        else if (strncmp(inStr, "PRE", 3) == 0){
            fgets(valStr, 10, stdin);
            val = atoi(valStr);
           
            printf("%i\n", getPre(*l, val));
        }
        else if (strncmp(inStr, "SUC", 3) == 0){
            fgets(valStr, 10, stdin);
            val = atoi(valStr);
           
            printf("%i\n", getSuc(*l,val));
        }
         else if (strncmp(inStr, "HEI", 3) == 0){
             
             printf("%i\n", getHeight(*l));
         }
        else{
        }
        
        
        
    }
    traverse(*l);
    
	return 1;
}
