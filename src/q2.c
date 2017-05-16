/**
 *	Giuliano Sovernigo			0948924
 *	CIS*2520_F16				A3: equations and heap
 *	11/7/2016
 *	This file contains the main function for the array-
 *	based heap constructor.  It passes along only the 
 *	file name, and error checks for the returned int
 *	pointer.
 */

#include "arrayHeap.h"
#include "fHeap.h"
#include <stdio.h>


int main()
{
	int err;
	char* fname = "./assets/f.dat";

	err = driver(fname);

	if(err != 0)
	{
		printf("Something went wrong!\n");
		if(err == -1)
		{
			perror("Unable to locate file requested.");
			printf("File was: %s\n",fname);
		}
	}

	
	return 0;
}
