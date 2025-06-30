#include "../include/parser.h" /* own header */
#include <stddef.h> /* For NULL */
#include <string.h> /* For strtok() */
#include <stdio.h> /* For fprintf() */

/*
 * divide_string:	gets full string and tokenize based on spaces
 *			Then give it to new array of pointers.
 *			If the number of arguments are above 32,
 *			it returns -1
 */
int tokenize_input(char *buffer, char **args)
{
	int i = 0;
	char *token = NULL;
	size_t num_of_arg = 0;

	token = strtok(buffer, " ");

	do {
		args[i++] = token;
		if (++num_of_arg > 32) {
			fprintf(stderr, "Too many arguments\n");
			/* Difference between fprintf(stderr, "message")
			 * and
			 * perror("some message").:
			 * perror:	For system/library call failure.
			 *		Add mes after system mes.
			 * fprintf:	For own error condition.
			 */
			return -1;
		}
	} while ((token = strtok(NULL, " "))); /* Intentional assign */

	args[i] = NULL; /* required for execvp(). */

	return num_of_arg;
}
