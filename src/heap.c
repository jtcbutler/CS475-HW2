/*
 * Heapsort implemented in the C programming language
 * 
 * Further documentation found in "heap.h"
 *
 * Created: Jan 20, 2025
 *  Author: Jackson Butler
 */

#include "heap.h"

#include "employee.h"
#include <stdio.h>

void heapSort(Employee *A, int n)
{
	// arrays of size 0 and 1 are considered sorted 
	if(n < 1) return;

	// build a min-heap
	buildHeap(A, n);

	// for every element in the heap
	// swap that element with the current root of the heap
	// call heapify to fix any min-heap violations that may have occured as a result of the swap
	for (int i = n - 1; i > 0; i--)
	{
		swap(&A[0], &A[i]);
		heapify(A, 0, i);
	}
}

void buildHeap(Employee *A, int n)
{
	// heapify all non-leaf elements within the heap
	for (int i = n/2 - 1; i >= 0; i--) heapify(A, i, n);
}

void heapify(Employee *A, int i, int n)
{
	// calculate the indicies of <i>s children
	int l = i*2+1;
	int r = l+1;

	// determine the index of the Employee with the smallest salary between <i> and its children
	// store the resulting index in <s>
	int s = i;
	if(l < n && A[l].salary < A[s].salary) s = l;
	if(r < n && A[r].salary < A[s].salary) s = r;

	// if either of <i>s children had a smaller salary, swap the two
	// call heapify to fix any min-heap violations that may have occured as a result of the swap
	if(s != i) 
	{
		swap(&A[s], &A[i]);
		heapify(A, s, n);
	}
}

void swap(Employee *e1, Employee *e2)
{
	Employee e3 = *e1;
	*e1 = *e2;
	*e2 = e3;
}

void printList(Employee *A, int n)
{
	// print a comma seperated list of each Employee structure in the array
	// structures are printed with the formatting "[id=<Employee.name>, sal=<Employee.salary>]"
	for(int i = 0; i < n; i++) 
	{
		printf("[id=%s sal=%d]", A[i].name, A[i].salary);

		if(i != n-1) printf(", ");
		else printf("\n");
	}
}
