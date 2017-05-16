/**
 *	Giuliano Sovernigo			0948924
 *	CIS*2520_F16				A3: equations and heap
 *	11/7/2016
 *	This file contains the main code for driving the program.  It contains 
 *	the menu, the array-access functions, and the solve function.  The 
 *	implimentation for these functions is contained in the c file of the 
 *	same name.
 */
#ifndef __GSOVERNIGO_DRIVER_H__
#define __GSOVERNIGO_DRIVER_H__
#include "tree.h"

#define MENU_TEXT "1) Display tree.\n2) Preorder display.\n3) Inorder display.\n4) Postorder display.\n5) Update variables.\n6) Calculate equation.\n7) Exit.\n"

/**
 *	menu
 *	This is the main menu function for the program.  It reads input from the
 *	user, and handles all the main code in the program.
 *	IN:		expression		- the expression that will be parsed and solved.
 *	OUT:	0 on success, negative error code on failure.
 *	POST:	an error code has been returned.
 *	ERROR:	expression is invalid or null.
 */
int menu(char* expression);

/**
 *	solve
 *	Solves a tree representing an order-of-operations equation that we have
 *	entered, and converted from expression
 *	IN:		tree			- the tree that will be solved.
 *			keys			- a table of all the variables that are going
 *							  to be used.
 *			vals			- a table of all the values for the variables
 *							  to be used.
 *			numVals			- the total number of variables currently.
 *			err				- an integer pointer that can be used to pass
 *							  error codes back to the previous function.
 *	OUT:	the solution to the tree, or 0 if there was an error.
 *	POST:	if the solution is 0, check err.  it may contain an error code
 *			that should be used to check for any problems that may have
 *			occurred.
 *	ERROR:	div by zero, invalid syntax, invalid format, you name it.
 */
float solve(TreeNode* tree, char* keys[], float vals[], int numVals, int* err);

/**
 *	addToTable
 *	adds all variable keys to the table of values, and adds their values to the
 *	same indexes in the vals table.
 *	IN:		tree			- the tree to be read from.
 *			table			- the table that stores all keys for variables.
 *			vals			- the table that stores the values for the keys in
 *							  table.
 *			numVars			- an integer pointer that will be updated as the 
 *							  program reads more variables in.
 *	OUT:	the number of variables written to the table.
 *	POST:	table, vals, and numvars will have been updated.
 *	ERROR:	tree, table, vals, or numVars are null.
 */
int addToTable(TreeNode* tree, char* table[], float vals[], int* numVars);

/**
 *	getFromTable
 *	gets a specific key's value from the table. Returns the value, or 0.
 *	IN:		key				- the key that will be searched for.
 *			table			- the table that will be searched using key.
 *			vals			- the table of values whose indexes are 
 *							  associated with table's
 *			numVals			- the number of values that are read in table.
 *	OUT:	the value of the key input, or 0.0 if none was found.
 *	POST:	a float has been returned
 *	ERROR:	key, table are invalid.  numVals is inaccurate.
 */
float getFromTable(char* key, char* table[], float vals[], int numVals);

/**
 *	update
 *	updates the variable tables, changing the value associated with key.
 *	IN:		key				- the key that will be searched for
 *			newVal			- the new value for key that will be put in vals.
 *			table			- the table of keys.
 *			vals			- the table of values (same index as in keys)
 *			numVals			- the number of values in table or vals.
 *	OUT:	0 on success, error code on failure.
 *	ERROR:	key is null, table is null, vals is null, or key does not exist
 *			in table (input is ignored.)
 */
int update(char* key, float newVal, char* table[], float vals[], int numVals);

#endif
