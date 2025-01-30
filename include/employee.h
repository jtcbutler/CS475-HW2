/*
 * This file contains the definition of the Employee structure
 * @author David (alterations made by Jackson Butler)
 */

#ifndef CS475_EMPLOYEE_H
#define CS475_EMPLOYEE_H

#define MAX_NAME_LEN 25

typedef struct 
Employee
{
	char name[MAX_NAME_LEN];
	int salary;
} 
Employee;

#endif
