/**
 *	Giuliano Sovernigo			0948924
 *	CIS*2520_F16				A3: equations and heap
 *	11/7/2016
 *
 *	This header file contains function and struct definitions for use in the
 *	c file of the same name.  They are intended for use on array-based binary 
 *	heaps, and the heap nodes in use use integer arrays as the data.
 */

#ifndef __GSOVERNIGO_ARRAYHEAP_H__
#define __GSOVERNIGO_ARRAYHEAP_H__

struct heap_node
{
	int key;
	int* data;
};

typedef struct heap_node HeapNode;

/**
 *	makeNode
 *	creates a new node from the 10 integer array that was passed in.
 *	IN:		data		- a 10-integer array.
 *			size		- the number of integers in the array MUST BE 10.
 *	OUT:	a new heapnode that can be added to an array heap.
 *	POST:	a new node has been created.  Dont forget to free it!!
 *	ERROR:	malloc fails
 */
HeapNode* makeNode(int data[], int size);

/**
 *	maxHeap
 *	uses a max heapifying algorithm to create a max heap.
 *	IN:		array		- the non-heap array to be heaped.
 *			size		- the size of the array.
 *	OUT:	0 on success, an error code on failure. (will be negative)
 *	POST:	array has been significantly changed if it is not in heap
 *			order prior to execution.
 *	ERROR:	array is null or size is not reflective of array's size.
 */
int maxHeap(HeapNode* array[], int size);

/**
 *	maxDownHeap
 *	downheaps a node, moving it down to its correct location.
 *	IN:		heap		- the heap that will be operated on.
 *			size		- the size of the heap.
 *			i			- the index of the element that will be downheaped.
 *	OUT:	0 on success, error code (negative) on failure.
 *	POST:	heap has been modified.
 *	ERROR:	heap is null, or size does not reflect the actual size.
 */
int maxDownHeap(HeapNode* heap[], int size, int i);

/**
 *	printHeap
 *	prints a heap in array form vertically on the screen.
 *	IN:		heap		- the heap to be printed.
 *			size		- the size of the heap-array.
 *	OUT:	the number of nodes that were printed.
 *	POST:	heap has been printed to the screen.
 *	ERROR:	heap is null, or size is not accurate to the actual size.
 */
int printHeap(HeapNode* heap[], int size);

/**
 *	swap
 *	swaps two indexes i and j, in the array heap.
 *	IN:		heap		- the heap to be operated on.
 *			size		- the size of the heap.
 *			i			- the first index of the heap to be swapped.
 *			j			- the second index of the heap to be swapped.
 *	OUT:	0 on success, negative error code on failure.
 *	POST:	heap has been modified, and indecies may be out of place.
 *	ERROR:	heap is null, i or j are invalid, or size is not reflective of
 *			the actual size of the heap (fatal)
 */
int swap(HeapNode* heap[], int size, int i, int j);

/**
 *	freeNode
 *	frees a node and its associated data.
 *	IN:		hn			- the heap node to be freed.
 *	OUT:	void
 *	POST:	hn->data has been freed, and hn has been freed.  Use with caution.
 *	ERROR:	none.
 */
void freeNode(HeapNode* hn);

#endif
