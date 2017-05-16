/**
 *	Giuliano Sovernigo			0948924
 *	CIS*2520_F16				A3: equations and heap
 *	11/7/2016
 *	This c file contains the code for the tree data
 *	structure manipulation.  Its declaration is in
 *	the header file of the same name.
 */
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

TreeNode* makeFloatNode(float f)
{
	TreeNode* n;

	n = malloc(sizeof(TreeNode));

	if(n == NULL)
	{
		return NULL;
	}
	n->left = NULL;
	n->right = NULL;
	n->d.n = f;
	n->t = NUMBER;

	return n;
}

TreeNode* makeOpNode(char c)
{
	TreeNode* n;

	n = malloc(sizeof(TreeNode));

	if(n == NULL)
	{
		return NULL;
	}
	n->left = NULL;
	n->right = NULL;
	n->d.o = c;
	n->t = OPERATOR;

	return n;

}

TreeNode* makeVarNode(char* c)
{
	TreeNode* n;

	n = malloc(sizeof(TreeNode));

	if(n == NULL)
	{
		return NULL;
	}
	n->left = NULL;
	n->right = NULL;
	n->d.v = c;
	n->t = VARIABLE;

	return n;
}	

int numElements(TreeNode* node)
{
	if(node == NULL) /* if we hit a leaf */
	{
		return 0;
	}
	return numElements(node->left) + numElements(node->right) + 1; /* add the depth of the left and the depth of the right, plus the current one. */
}

int depth(TreeNode* n)
{
	int depthL;
	int depthR;

	depthL = 0;
	depthR = 0;

	if(n == NULL)
	{
		return 0;
	}
	
	depthR = depth(n->right); /* recursively call the __depth function for left and right */
	depthL = depth(n->left);

	return (depthR > depthL)? depthR : depthL; /* return the larger of the two */
}

int treeIsEmpty(TreeNode* t)
{
	if(t == NULL)
	{
		return 1;
	}
	return 0;
}

TreeNode* children(TreeNode* parent, TreeNode** left, TreeNode** right)
{
	if(parent == NULL)
	{
		return NULL;
	}
	else
	{
		*left = parent->left;
		*right = parent->right;
	}

	return parent;
}

TreeNode* left(TreeNode* parent)
{
	if(parent == NULL)
	{
		return NULL;
	}	

	return parent->left;
}

TreeNode* right(TreeNode* parent)
{
	if(parent == NULL)
	{
		return NULL;
	}

	return parent->right;
}


int postOrder(TreeNode* tree)
{
	int actions;
	
	actions = 1;

	if(tree->left != NULL)
	{
		actions += postOrder(tree->left);
	}
	if(tree->right != NULL)
	{
		actions += postOrder(tree->right);
	}

	printNode(tree);

	return actions;
}

int preOrder(TreeNode* tree)
{
	int actions;
		
	actions = 1;

	printNode(tree);

	if(tree->left != NULL)
	{
		actions += preOrder(tree->left);
	}
	if(tree->right != NULL)
	{
		actions += preOrder(tree->right);
	}

	return actions;
}

int inOrder(TreeNode* tree)
{
	int actions;

	actions = 1;
	

	if(tree->left != NULL)
	{
		printf("(");
		inOrder(tree->left);
	}
	
	printNode(tree);

	if(tree->right != NULL)
	{
		inOrder(tree->right);
		printf(")");
	}

	return actions;
}

void printNode(TreeNode* n)
{
	if(n == NULL)
	{
		return;
	}
	if(n->t == OPERATOR)  // printing the operator.
	{
		printf("%c ",n->d.o); 
	}
	else if(n->t == NUMBER)
	{
		printf("%.2f ",n->d.n); // printing a number
	}
	else if(n->t == VARIABLE) // printing a variable
	{
		printf("%s ",n->d.v);
	}
}


int printTree(TreeNode* tree, int level)
{
	int i;
	if(tree == NULL)
	{
		return -1;
	}


	for(i = 0; i < level; i++)
	{
		printf("|    ");
	}
	printf("\n");
	for(i = 0; i < level; i++)
	{
		printf("|    ");
	}
	printf("\n");


	for(i = 0; i < level-1; i++)
	{
		printf("|    ");
	}

	if(level != 0 )
	{
		printf("====="); // print the sub-item branch.
	}

	printNode(tree);	
	printf("\n");

	if(tree->left != NULL) // if we have a left child
	{
		printTree(tree->left, level + 1);
	}

	if(tree->right != NULL)
	{
		printTree(tree->right, level + 1);
	}
	return 0;
}

void deleteTree(TreeNode* tree)
{
	if(tree == NULL)
	{
		return;
	}

	if(tree->left != NULL)
	{
		deleteTree(tree->left);
	}
	
	if(tree->right != NULL)
	{
		deleteTree(tree->right);
	}

	if(tree->t == VARIABLE)
	{
		free(tree->d.v);
	}
	free(tree);
}	


