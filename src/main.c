/*
 * A program implementing heapSort() as defined in "heap.c"
 *
 * Created: Jan 29, 2025
 *  Author: Jackson Butler
 */

#include "employee.h"
#include "heap.h"
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

#define MAX_EMPLOYEES 5

/*
 * Read a string from the user into an Employee structures name member
 *
 * @param Employee* <employee> - the Employee structure whose name should be set
 * @param char* <name_buffer> - the buffer for recieving user input
 * @param int <name_buffer_size> - the size of <name_buffer>
 *
 * @return int - error code
 *
 * @error -1 - fgets() failed to read from stdin
 * @error -2 - the name entered was larger than the provided buffer
 *
 * WARNING: if <name_buffer_size> is larger than <MAX_NAME_LEN + 1> a buffer overflow may occur
 */
int readEmployeeName(Employee *employee, char *name_buffer, int name_buffer_size);

/*
 * Read an integer from the user into an Employee structures salary member
 *
 * @param Employee* <employee> - the Employee structure whose salary should be set
 * @param char* <salary_buffer> - the buffer for recieving user input
 * @param int <salary_buffer_size> - the size of <salary_buffer>
 *
 * @return int - error code
 *
 * @error -1 - fgets() failed to read from stdin
 * @error -2 - the salary entered was too large to fit inside of an <int>
 * @error -3 - the salary entered was negative
 * @error -4 - the salary entered was not an integer value
 * @error -5 - the salary entered contained non-numeric characters
 */
int readEmployeeSalary(int *salary, char *salary_buffer, int salary_buffer_size);

/*
 * Wrapper for fgets() that is tuned to the needs of this program
 *
 * @param char *restrict <s> - the buffer that should be read into
 * @param int <size> - the size of <s>
 * @param FILE *restrict <stream> - the file stream from which text should be read
 *
 * @return int - the length of the strin read or an error code
 *
 * @error -1 - fgets() failed to read from stdin
 * @error -2 - the string entered was larger than the provided buffer
 */
int fgetsWrapper(char *restrict s, int size, FILE *restrict stream);

/*
 * Wrapper for atoi() that is tuned to the needs of this program
 *
 * @param const char* <nptr> - the string to parse
 *
 * @return int - the parsed integer value or an error code
 *
 * @error -1 - a negative value entered (string began with '-')
 * @error -2 - a decimal value entered (string contained '.')
 * @error -3 - another non-numeric character entered
 * @error -4 - the parsed number was too large to fit into an int
 *
 * NOTE: unlike atoi() this function is designed to only work with unsigned numbers
 */
int atoiWrapper(const char *nptr);

int main(void)
{
	// heap allocate an array of size <MAX_EMPLOYEES>
	// once populated this array will be fed to heapSort()
	Employee *employee_array = (Employee*) malloc(sizeof(Employee) * MAX_EMPLOYEES);

	// heap allocate a buffer for user input of employee names
	// the buffer is one element larger than the final name array
	// this accounts for the newline at the end of user input
	int name_buffer_size = MAX_NAME_LEN + 1;
	char *name_buffer = (char*)malloc(sizeof(char) * name_buffer_size);

	// ensure that neither of the above allocations failed
	if(employee_array == NULL || name_buffer == NULL)
	{
		fprintf(stderr, "A necessary memory allocation has failed. EXITING PROGRAM\n");
		fprintf(stderr, "Exiting program...\n");
		return EXIT_FAILURE;
	}

	// stack allocate a buffer for user input of employee salaries
	// the buffer is large enough to hold the text representation of INT_MAX plus a newline and null terminator
	// at most the size of this array will be 22 bytes (if the system supports 64-bit <int>s) which poses no risk of a stack overflow
	int salary_buffer_size = (((int)log10(INT_MAX)) + 3);
	char salary_buffer[salary_buffer_size];

	// populate each employee in the array
	for(int i = 0; i < MAX_EMPLOYEES; i++) 
	{
		// continue attempting to read a name until successful
		while(1)
		{
			printf("Name: ");

			// read a name
			// if there is an error, report it and try again
			switch(readEmployeeName(&employee_array[i], name_buffer, name_buffer_size))
			{
				case -1: fprintf(stderr, "There was an error reading your input, please try again\n"); continue;
				case -2: fprintf(stderr, "Valid names must have a length less than or equal to %d characters\n", MAX_NAME_LEN - 1); continue;
			}

			// if no error occurred, exit the loop
			break;
		}

		// continue attempting to read a salary until successful
		while(1)
		{
			printf("Salary: ");

			// read a salary
			// if there is an error, report it and try again
			switch(readEmployeeSalary(&employee_array[i].salary, salary_buffer, salary_buffer_size))
			{
				case -1: fprintf(stderr, "There was an error reading your input, please try again\n"); continue;
				case -2: fprintf(stderr, "Valid salaries must have a value less than or equal to $%d\n", INT_MAX); continue;
				case -3: fprintf(stderr, "Valid salaries may only be positive values\n"); continue;
				case -4: fprintf(stderr, "Valid salaries may only be dollar values\n"); continue;
				case -5: fprintf(stderr, "Valid salaries may only contain numeric characters\n"); continue;
			}

			// if no error occurred, exit the loop
			break;
		}

		printf("\n");
	}

	// free the name buffer, it is no longer needed
	free(name_buffer);

	// sort the employee array and print the result
	heapSort(employee_array, MAX_EMPLOYEES);
	printList(employee_array, MAX_EMPLOYEES);

	// free the employee array and exit the program
	free(employee_array);
	return EXIT_SUCCESS;
}

int readEmployeeName(Employee *employee, char *name_buffer, int name_buffer_size)
{
	// read a name
	// if an error occured, return its code
	// otherwise, copy the name read into <name_buffer> over to <employee->name>
	// return 0 to indicate that no error occured
	int error = fgetsWrapper(name_buffer, name_buffer_size, stdin);
	if(error < 0) return error;
	strcpy(employee->name, name_buffer);
	return 0;
}

int readEmployeeSalary(int *salary, char *salary_buffer, int salary_buffer_size)
{
	// read a salary
	// if an error occured, return its code
	int error = fgetsWrapper(salary_buffer, salary_buffer_size, stdin);
	if(error < 0) return error;

	// attempt to parse the salary read into <salary_buffer>
	// check for possible errors, if an error occured, return the corresponding code
	error = atoiWrapper(salary_buffer);
	switch(error)
	{
		case -1: return -3;
		case -2: return -4;
		case -3: return -5;
		case -4: return -2;
	}

	// copy the parsed salary into <employee->salary>
	// return 0 to indicate that no error occurred
	*salary = error;
	return 0;
}

int fgetsWrapper(char *restrict s, int size, FILE *restrict stream)
{
	// call fgets() with the arguments passed to this function
	// if an error occurs, return -1 to indicate that fgets() has failed
	if(fgets(s, size, stream) == NULL) return -1;

	// determine the length of the string read into <s>
	int len = strlen(s);

	// if the last character of the string read into <s> is not '\n' the users input was cut off
	// clear <stdin> of the user inputs remnants using getchar()
	// return -2 to indicate that the inputs length exceeded the buffers size
	if(s[len-1] != '\n')
	{
		while(getchar() != '\n');
		return -2;
	}

	// truncate the newline character with a null terminator
	// return the new length of the string read into <s>
	s[len-1] = '\0';
	return len - 1;
}

int atoiWrapper(const char *nptr)
{
	// scan the entire string for invalid characters
	// if an invalid character is found, return is corresponding error code
	int len = strlen(nptr);
	for(int i = 0; i < len; i++)
	{
		if(!isdigit(nptr[i]))
		{
			if(i == 0 && nptr[0] == '-') return -1;
			if(nptr[i] == '.') return -2;
			else return -3;
		}
	}

	// call atoi() with the arguments passed to this function
	// if the result of atoi() is negative, there was overflow, return the corresponding error code
	// otherwise, return the parsed integer
	int parsed_int = atoi(nptr);
	return (parsed_int < 0) ? -4 : parsed_int;
}
