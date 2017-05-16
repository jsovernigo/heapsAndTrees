/**
 *	Giuliano Sovernigo			0948924
 *	CIS*2520_F16				A3: equations and heap
 *	11/7/2016
 *
 *  This c file contains the code for the functions defined in the header file
 *  of the same name.  These functions are intended for operation on array-
 *  based heaps, where the data associated with nodes are integer arrays of 
 *  size 10.
 */


#include "arrayHeap.h"
#include <stdlib.h>
#include <stdio.h>

HeapNode* makeNode(int data[], int size)
{
	int i;
	HeapNode* newNode;

	newNode = malloc(sizeof(newNode));
	if(newNode == NULL)
	{
		return NULL;
	}
	newNode->data = malloc(sizeof(int) * size);
	if(newNode->data == NULL)
	{
		free(newNode);
		return NULL;
	}

	for(i = 0; i < size; i++) /* loops through data's integers */
	{
		newNode->data[i] = data[i];
	}

	newNode->key = data[0] + data[1] + data[2]; /* this will be the sorting key */

	return newNode;
}

int maxHeap(HeapNode* array[], int size)
{
	int i;

	if(array == NULL)
	{
		return -1;
	}	

	if(size <= 0) /* cannot heapify an empty list */
	{
		return -1;
	}
	for(i = size/2; i > 0; i--) /* loops from the halfway point to 0 (all parents) */
	{
		maxDownHeap(array, size, i); /* downheap each node */
	}
	return 0;
}

int maxDownHeap(HeapNode* heap[], int size, int i)
{
	if(i > size || heap == NULL)
	{
		return -1;
	}


	if(2*i+1 >= size) /* this is only needed if a heap is not padded on the end with NULL values. */
	{
		if(2*i >= size)
		{
			return -1;
		}
		else if(heap[i]->key < heap[2*i]->key) /* if we have a child but ONLY one, and it is swapable */
		{
			swap(heap, size, i, 2*i);
			maxDownHeap(heap, size, 2*i);
			return 0;
		}
		
	}

	if(heap[2*i] != NULL && heap[i]->key < heap[2*i]->key && heap[2*i-1] != NULL && heap[i]->key < heap[2*i+1]->key)
	{
		if(heap[2*i]->key > heap[2*i+1]->key) /* we will swap heap[2*i] because it is bigger. */
		{
			swap(heap, size, i, 2*i);
			maxDownHeap(heap, size, 2*i);
		}
		else /* the other child is the one that we will swap. */
		{
			swap(heap, size, i, 2*i+1);
			maxDownHeap(heap, size, 2*i+1);
		}
	}
	else if(heap[2*i] != NULL && heap[i]->key < heap[2*i]->key) /* heap at the child value exists and contains a key greater than parents */
	{
		swap(heap, size, i, 2*i);
		maxDownHeap(heap, size, 2*i);
	}
	else if(heap[2*i+1] != NULL && heap[i]->key < heap[2*i+1]->key) /* heap child value exists, and contains a key that is greater than the parents. */
	{
		swap(heap, size, i, 2*i+1);
		maxDownHeap(heap, size, 2*i+1);
	}

	return 0;
}

int printHeap(HeapNode* heap[], int size)
{
	int i;
	int printed;

	printed = 0;

	if(heap == NULL)
	{
		return -1;
	}

	printf("Key:\tData:\n"); /* prints the header for the data dump */
	
	for(i = 1; i < size; i++) /* loop through the nodes, printing them. */
	{
		if(heap[i] != NULL)
		{
			int j;

			printf("(%d)\t",heap[i]->key);
			for(j = 0; j < 10; j++) /* loop through each member of the array of data. */
			{
				if(heap[i]->data[j] < 10) /* this accounts for leading 0s */
				{
					printf("0%d ", heap[i]->data[j]);
				}
				else /* dont print a leading 0. */
				{
					printf("%d ", heap[i]->data[j]);
				}
			}
			printed++;
			printf("\n");
		}
		else
		{
			return printed;
		}
	}
	return printed;
}

int swap(HeapNode* heap[], int size, int i, int j)
{
	HeapNode temp;
	if(heap == NULL)
	{
		return -1;
	}
	else if (i >= size || j >= size) /* if i or j are invalid */
	{
		return -2;
	}
	else /* you know the drill... 3 line swap. */
	{
		temp = *heap[i];
		*heap[i] = *heap[j];
		*heap[j] = temp;
	}
	return 0;
}

void freeNode(HeapNode* hn)
{
	if(hn != NULL)
	{
		free(hn->data);
	}
	free(hn);
	return;
}
