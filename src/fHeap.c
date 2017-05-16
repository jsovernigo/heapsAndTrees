/**
 *	Giuliano Sovernigo			0948924
 *	CIS*2520_F16				A3: equations and heap
 *	11/7/2016
 *
 * 	This c file contains the main code for the program.  It creates a heap
 * 	from data in a data file, then prints it out after heapifying the data.
 *  The definition for this function can be found in the header file of the
 *  same name.
 */
#include "fHeap.h"
#include "arrayHeap.h"
#include <stdio.h>

int driver(char* fname)
{
	int i;
	FILE* dataFile;

	HeapNode* heap[21];

	dataFile = fopen(fname,"r");
	if(dataFile == NULL)
	{
		return -1;
	}

	heap[0] = NULL; /* this is the dummy head of the heap. */

	for(i = 1; i < 21; i++) /* loop through the array objects */
	{
		int j;
		int values[10];
		char line[256];
		HeapNode* newNode;

		fgets(line, 128, dataFile);
		
		for(j = 0; j < 10; j++) /* loop through the numbers */
		{
			int val;
			sscanf(line+3*j,"%d ", &val); /* get the next number */
			values[j] = val;
		}

		newNode = makeNode(values,10);

		heap[i] = newNode; /* add the new node to the array */
	}
	
	printf("Before partial ordering:\n");
	printHeap(heap,21);
	printf("\n");

	maxHeap(heap,21); /* this heapifies the currently random heap */

	printf("Now heapified:\n");
	printHeap(heap,21);
	printf("\n");

	for(i = 0; i < 21; i++)
	{
		freeNode(heap[i]);
	}
	return 0;
}
