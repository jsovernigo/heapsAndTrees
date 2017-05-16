/**
 *	Giuliano Sovernigo			0948924
 *	CIS*2520_F16				A3: equations and heap
 *	11/7/2016
 *	this function contains the declaration for the 
 *	verifying and tree-ifying functions that are used
 *	to parse equations and turn them into trees.
 */

#include "tree.h"
#ifndef __GSOVERNIGO_VERIFY_H__
#define __GSOVERNIGO_VERIFY_H__

#define DIVIDE_BY_ZERO -1
#define INVALID_OPERATOR -2
#define NULL_TREE -3
#define SYNTAX_ERROR -4

/**
 *	operate
 *	operates on the two floats passed in, based on op's value.
 *	IN:		num1		- the first floating point number that will be modified
 *			num2		- the second floating point number.
 *			op			- the character that represents the operator.
 *			err			- an integer pointer that will be updated to an error
 *						  code in case of an error (probably divide by zero...)
 *	OUT:	the answer, or 0 if divide by zero.
 *	POST:	an integer has been returned.
 *	ERROR:	divide by zero
 */
float operate(float num1, float num2, char op, int* err);

/**
 *	makeFromExpression
 *	creates a tree from a character expression in the form (aob), where:
 *		a is the first operand
 *		o is the operator,
 *		b is the second operand.
 *	IN:		expression	- the expression that will be tree'd
 *	OUT:	a new node with two parents.
 *	POST:	a tree node has been returned with TWO children.
 *	ERROR:	expression is null, malloc fails, etc. 
 */
TreeNode* makeFromExpression(char* expression);

/**
 *	assembleTree
 *	assembles a tree from an expression, such that order of operations is kept.
 *	IN:		expression	- the expression that is to be converted into a tree.
 *	OUT:	a treenode which contains the representation of the expression in
 *			expression.
 *	POST:	a whole tree has been passed back, and should be freed when you're
 *			finished with it.
 *	ERROR:	expression is faulty or malloc/regcomp fails.	
 */
TreeNode* assembleTree(char* expression);

/**
 *  substr
 *  Returns a malloc'd substring representing the substring from i to j in str.
 *  IN:		str			- a string that will have substrings made from it.
 *  		i			- the earlier index.
 *  		j			- the later index.
 *  OUT:	a new malloc'd substring.  Enjoy.
 *  POST:	the malloc'd return value should be freed eventually.
 *  ERROR:	str is null, i and j are invalid, or j preceeds i.
 */
char* substr(char* str, int i, int j);

#endif
