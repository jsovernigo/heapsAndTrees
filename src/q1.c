/**
 *	Giuliano Sovernigo			0948924
 *	CIS*2520_F16				A3: equations and heap
 *	11/7/2016
 *	This is the main function for the equation-solving
 *	tree.  It passes arguments along.
 */

#include "driver.h"
#include <stdio.h>
#include <string.h>


int main(int argc, char** argv)
{
	int result;
	char expression[256];

	if(argc != 2)
	{
		printf("Incorrect usage.  Please use as:\n\t%s <expression>\n",argv[0]);
		return 1;
	}
	else
	{
		strcpy(expression, argv[1]);
	}

	result = menu(expression);
	if(result != 0)
	{
		printf("Whoops, something went wrong.\n");
	}
	return 0;
}
