/**
 *	Giuliano Sovernigo			0948924
 *	CIS*2520_F16				A3: equations and heap
 *	11/7/2016
 *	This file contains the main code for driving the program.  
 *  It contains the menu, the array-access functions, and the
 *  solve function.  The declaration for these functions is 
 *	contained in the H file of the same name.
 */

#include "driver.h"
#include "tree.h"
#include "verify.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int menu(char* expression)
{
	char* keys[10];
	float vals[10];
	
	int numEntries;
	int choice;
	int* err;

	TreeNode* tree;

	choice = 0;
	numEntries = 0;
	err = malloc(sizeof(int));
	if(err == NULL)
	{
		return -1;
	}

	tree = assembleTree(expression); // creates a new tree out of the expression.

	if(tree == NULL)
	{
		return -1;
	}

	addToTable(tree, keys, vals, &numEntries); // adds all variables to a set of key-value arrays.

	do
	{
		int result;
		char line[64];

		printf("%s", MENU_TEXT);

		fgets(line, 63, stdin);
		result = sscanf(line, "%d", &choice); // gets the user's choice.
		if(result == 0)
		{
			choice = -1;
			continue;
		}

		if(choice == 1) // print the tree
		{
			int i;
			for(i = 0; i < numEntries; i++)
			{
				printf("%s: %f  ",keys[i], vals[i]); // prints each variable.
			}
			printTree(tree,0);
		}
		else if(choice == 2) // preorder selected
		{
			printf("Preordered:\n");
			preOrder(tree);
			printf("\n");
		}
		else if(choice == 3) // Inorder selected
		{
			printf("Inordered:\n");
			inOrder(tree);
			printf("\n");
		}
		else if(choice == 4) // Postorder selected.
		{
			printf("Postordered:\n");
			postOrder(tree);
			printf("\n");
		}
		else if(choice == 5)
		{
			char variable[20];
			char valBuff[20];
			float value;
			short changed;

			value = 0;
			changed = 0;

			printf("Please enter a variable designation (x1-9):\n");
			fgets(variable, 20, stdin);
			*(strchr(variable,'\n')) = '\0'; 
			do
			{
				int numRead;

				printf("Please enter a new value for %s:\n",variable);
				fgets(valBuff, 20, stdin);
				numRead = sscanf(valBuff, "%f", &value);

				if(numRead != 1)
				{
					changed = 0;
				}
				else // the variable has been read in!
				{
					changed = 1;
				}
			}while(changed == 0);

			update(variable, value, keys, vals, numEntries);
		}
		else if(choice == 6)
		{
			float result;

			printf("Solving: %s\n",expression);
			result = solve(tree, keys, vals, numEntries, err);

			if(*err != 0)
			{
				printf("Something went wrong in solving the expression.\n");
				if(*err == DIVIDE_BY_ZERO)
				{	
					printf("There is a divide by zero present in the equation.\n");
				}
				else if(*err == SYNTAX_ERROR)
				{
					printf("There is a syntax error present in the equation.\n");
				}
			}
			else
			{
				printf("The solution to the equation is %.2f\n", result);
			}
		}
		else if(choice == 7)
		{
			deleteTree(tree);
			free(err);
		}
		else
		{
			printf("Cannot understand input.\n");
		}

	}while(choice != 7);

	printf("Goodbye!\n");

	return 0;
}

float solve(TreeNode* tree, char* keys[], float vals[], int numVals, int* err)
{
	float result;
	if(err == NULL)
	{
		return 0;
	}
	else
	{
		*err = 0;
	}
	if(tree == NULL)
	{
		*err = NULL_TREE;
		return 0;
	}
	
	if(tree->left == NULL && tree->right == NULL)
	{
		if(tree->t == NUMBER) // if the tree is a number
		{
			return tree->d.n;
		}
		else if(tree->t == VARIABLE)
		{
			return getFromTable(tree->d.v, keys, vals, numVals);
		}
		else
		{
			*err = SYNTAX_ERROR;
			return 0;
		}
	}
	else
	{
		if(tree->t == OPERATOR)
		{
			float num1;
			float num2;
			char operator;

			num1 = solve(tree->left,keys,vals,numVals,err);
			if(*err != 0)
			{
				return 0;
			}
			num2 = solve(tree->right,keys,vals,numVals,err);
			if(*err != 0)
			{
				return 0;
			}
			operator = tree->d.o;
			result = operate(num1, num2, operator, err);
			if(*err != 0)
			{
				return 0;
			}
			
			return result;
		}
		else
		{
			*err = SYNTAX_ERROR;
			return 0;
		}
	}
	return 0.0;
}

int addToTable(TreeNode* tree, char* table[], float vals[], int* numVars)
{
	if(tree == NULL)
	{
		return -1;
	}
	else if(numVars == NULL)
	{
		return -2;
	}

	if(tree->t == VARIABLE)
	{
		table[*numVars] = tree->d.v; // adds the variable name to the function.
		vals[*numVars] = 0.0;
		*numVars += 1;
	}
	if(tree->left != NULL)
	{
		addToTable(tree->left, table, vals, numVars); // add anything of the left
	}
	if(tree->right != NULL)
	{
		addToTable(tree->right, table, vals, numVars); // add anything on the right.
	}

	return 0;
}

float getFromTable(char* key, char* table[], float vals[], int numVals)
{
	int i;

	for(i = 0; i < numVals; i++)
	{
		if(strcmp(table[i],key) == 0) // searches through the keys.
		{
			return vals[i];
		}
	}

	return 0.0;
}

int update(char* key, float newVal, char* table[], float vals[], int numVals)
{
	int i;

	if(key == NULL)
	{
		return -1;
	}

	for(i = 0; i < numVals; i++)
	{
		if(strcmp(key, table[i]) == 0)
		{
			vals[i] = newVal;
			return 0;
		}
	}
	return 1;
}
