/**
 *	Giuliano Sovernigo			0948924
 *	CIS*2520_F16				A3: equations and heap
 *	11/7/2016
 *
 *	This very simple header file contains a single function which is used to
 *	read from a file and then heapify an array based heap of integer arrays.
 */
#ifndef __GSOVERNIGO_FHEAP_H__
#define __GSOVERNIGO_FHEAP_H__

/**
 *	driver
 *	This is the body of the program.  It reads in from a file the data for
 *	the heap to store, then creates a heap from the data, max heaping it.
 *	IN:		fname		- the file name that will be read from.
 *	OUT:	0 on success, negative error code on failure.
 *	POST:	a heap has been printed to the screen.
 *	ERROR:	malloc fails, file does not exist (various)
 */
int driver(char* fname);

#endif
