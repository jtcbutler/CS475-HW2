/*
 * This file contains the declaration of heapSort() and its helper functions
 *
 * heapSort() works with arrays of the Employee structure defined in "employee.h"
 *
 * Created: Jan 20, 2025
 *  Author: Jackson Butler
 */

#ifndef CS475_HEAP_H
#define CS475_HEAP_H

#include "employee.h"

/*
 * Sorts an array of n employees in descending order
 *
 * @param	Employee* <A>	- the array of Employee structures
 * @param	int <n> - the arrays length
 */
void heapSort(Employee *A, int n);

/*
 * Reorders an array turning it into a valid min-heap
 *
 * @param	Employee* <A> - the array of Employee structures
 * @param	int <n>	- the arrays length
 */
void buildHeap(Employee *A, int n);

/*
 * Reorders a given elements subtree such that it is a valid min-heap
 *
 * @param	Employee* <A>	- the array of Employee structures
 * @param	int <i> -	the index of the element to heapify
 * @param	int <n> -	the arrays length
 */
void heapify(Employee *A, int i, int n);

/*
 * Swaps the locations of two Employee structures
 *
 * @param Employee* <e1> - the first Employee structure
 * @param Employee* <e2> - the second Employee structure
 */
void swap(Employee *e1, Employee *e2);

/*
 * Prints an array of Employee structures
 *
 * @param	Employee* <A>	- the array of Employee structures to print
 * @param	int <n> - the arrays length
 */
void printList(Employee *A, int n);

#endif
