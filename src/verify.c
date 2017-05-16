/**
 *	Giuliano Sovernigo			0948924
 *	CIS*2520_F16				A3: equations and heap
 *	11/7/2016
 *	this function contains the implimentation for the 
 *	verifying and tree-ifying functions that are used
 *	to parse equations and turn them into trees.
 */

#include "verify.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>


float operate(float num1, float num2, char op, int* err)
{
	if(op == '+')
	{
		return num1 + num2;
	}
	else if (op == '-')
	{
		return num1 - num2;
	}
	else if (op == '*')
	{
		return num1 * num2;
	}
	else if (op == '/') // division
	{
		if(num2 == 0) // divide by zero...
		{
			if(err != NULL) // if we did not get valid err value.
			{
				*err = DIVIDE_BY_ZERO;
			}

			return 0;
		}
		else
		{
			return num1 / num2; 
		}
	}
	*err = INVALID_OPERATOR; // transmit the error code for invalid operator.
	return 0;
}

TreeNode* makeFromExpression(char* expression)
{
	unsigned int i;
	float value1;
	float value2;
	int buffPos;
	char operator;
	int success;
	int secondFlag;
	int dontRead;

	char buff[5];
	char* variable;
	regex_t pattern;

	TreeNode* newTree;
	TreeNode* newLeft;
	TreeNode* newRight;

	newTree = NULL;
	newLeft = NULL;
	newRight = NULL;

	buffPos = 0;
	dontRead = 0;
	secondFlag = 0;
	operator = '\0';
	buff[0] = '\0';

	success = regcomp(&pattern, "([0-9]+([.][0-9]+)?|x[0-9])[-+/*]([0-9]+([.][0-9]+)?|x[0-9])", REG_EXTENDED); // regex for a basic expression.
	if(success != 0)
	{
		return NULL;
	}

	if(regexec(&pattern, expression, 0, NULL, 0) != 0) // if we match the regex for an equation
	{
		return NULL;
	}
	regfree(&pattern);

	for(i = 0u; i < strlen(expression); i++)
	{
		if(dontRead == 0 && strchr("1234567890.", expression[i]) != NULL) // if the character is a number or decimal
		{
			buff[buffPos] = expression[i];
			buffPos++;
		}
		else if(strchr("+-/*",expression[i]) != NULL) // found the operator.
		{
			if(buff[0] != '\0')
			{
				value1 = atof(buff);
				newLeft = makeFloatNode(value1);
			}
			operator = expression[i];
			memset(buff,'\0', 5); // clear the memory
			buffPos = 0; // reset the counter for buff
			dontRead = 0;
			secondFlag = 1;
		}
		else if(expression[i] == 'x')
		{
			variable = malloc(sizeof(char)*4); 
			variable[0] = 'x';
			variable[1] = expression[i+1];
			if(isdigit(expression[i+2]))
			{
				variable[2] = expression[i+2];	
				variable[3] = '\0';
			}
			else
			{
				variable[2] = '\0';
			}
			dontRead = 1;
			if(secondFlag == 0)
			{
				newLeft = makeVarNode(variable);
			}
			else
			{
				newRight = makeVarNode(variable);
			}
		}
	}
	if(buff[0] != '\0')
	{
		value2 = atof(buff);
		newRight = makeFloatNode(value2);
	}

	if(operator == '\0')
	{
		return NULL;
	}

	newTree = makeOpNode(operator);
	newTree->left = newLeft;
	newTree->right = newRight;

	return newTree;
}

TreeNode* assembleTree(char* expression)
{
	unsigned int i;
	int success;
	int parenLevel;
	regex_t pattern;
	regex_t number;
	regex_t variable;

	parenLevel = 0;
	
	success = regcomp(&variable, "^x[1-9][1-9]?$", REG_EXTENDED);
	if(success != 0)
	{
		return NULL;
	}

	if(regexec(&variable, expression, 0, NULL, 0) == 0)
	{
		char* var;
		var = malloc(sizeof(char)*4);
		TreeNode* n;

		strncpy(var, expression, 3);
		var[3] = '\0';

		n = makeVarNode(var);
		
		regfree(&variable);
		return n;
	}
	regfree(&variable);

	success = regcomp(&number, "^[0-9]+([.][0-9]+)?$", REG_EXTENDED);
	if(success != 0)
	{
		return NULL;
	}
	
	if(regexec(&number, expression, 0, NULL, 0) == 0)
	{
		TreeNode* n;

		n = makeFloatNode(atof(expression));

		regfree(&number);
		return n;
		
	}
	regfree(&number);
	
	success = regcomp(&pattern, "^\\(([0-9]+([.][0-9]+)?|x[0-9])[-+/*]([0-9]+([.][0-9]+)?|x[0-9])\\)$", REG_EXTENDED);
	if(success != 0)
	{
		return NULL;
	}

	if(regexec(&pattern, expression, 0, NULL, 0) == 0)
	{
		TreeNode* tn;

		tn = makeFromExpression(expression); // makes the 3-element tree for this expression.
		regfree(&pattern);
		return tn;
	}

	regfree(&pattern);

	for(i = 0u; i < strlen(expression); i++)
	{
		if(expression[i] == '(')
		{
			parenLevel++;
		}
		else if(expression[i] == ')')
		{
			parenLevel--;
			if(parenLevel < 0)
			{
				return NULL;
			}
		}
		else if(strchr("+-/*",expression[i]) != NULL)
		{
			if(parenLevel == 1)
			{
				char* subl;
				char* subr;
				TreeNode* newParent;
				subl = substr(expression, 1, i);
				subr = substr(expression, i+1, strlen(expression) - 1);

				newParent = makeOpNode(expression[i]);
				newParent->left = assembleTree(subl);
				newParent->right = assembleTree(subr);

				free(subl);
				free(subr);
				return newParent;
			}
		}
	}
	return NULL; // this is a problem-case.  If nothing logical was found, this is returned.
}

char* substr(char* str, int start, int end)
{
	int i;
	int len;
	char* substr;

	len = strlen(str); // dont need to worry about null string, since that will produce... 0.

	if(len == 0 || start >= len || start >= end || end > len || start < 0 || end < 0)
	{
		return NULL;
	}

	substr = malloc(sizeof(char)*(end - start + 1));
	if(substr == NULL)
	{
		return 0;
	}

	for(i = start; i < end; i++)
	{
		substr[i-start] = str[i];
	}
	substr[i-start] = '\0';

	return substr;
}
/*

   expression = "((((3+2)-1)/4)*5)"

   ordered_ops = []

#finds the primary operator for the bracket.
def get_prime_op(str_expression):

parenthesis = 0;
bstack = []
print "checking: ",str_expression
for i in range(0,len(str_expression)):
if str_expression[i] == '(':
parenthesis += 1
bstack.append('(')
elif str_expression[i] == ')':
bstack.pop();
elif str_expression[i] in "/+-*":
if len(bstack) == 1:
ordered_ops.append(str_expression[i])
ordered_ops.append(get_prime_op(str_expression[1:i]))
ordered_ops.append(get_prime_op(str_expression[i+1:len(str_expression)-1]))
return
elif len(bstack) == 0:
ordered_ops.append(str_expression[i])
return

get_prime_op(expression)

print ordered_ops

*/
