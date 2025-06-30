#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* declaration */
int is_blank_string(char *buffer, size_t buff_size);
size_t tokenize_input(char *buffer, char **args);

int main(void)
{
	char *buffer = NULL;
	size_t buff_size = 0;
	size_t characters;
	size_t input_len;
	int i;

	while (1) {
		printf("[bumshell]$ ");

		characters = getline(&buffer, &buff_size, stdin);
		/*
		 * getline returns num of char including '\n' 
		 * so, we need to create input_len
		 * for later functionalies.
		 */
		input_len = characters > 0 ? characters - 1 : 0;

		/* exit when EOF(C-d) typed */
		if (characters == -1) {
			printf("\n");
			free(buffer);
			exit(EXIT_SUCCESS);
		}

		/* take out \n */
		buffer[strcspn(buffer, "\n")] = '\0';

		/* check if it is a blank or no input at all. */
		if (is_blank_string(buffer, input_len)) {
			continue;
		}

		/* 
		 * TODO:
		 * FROM HERE: dealing with input string 
		 */

		char *args[32]; /* array of pointers */
		int num_of_arg;

		/*
		 * tokenize the user input based on spaces
		 */
		/* FUNCTION: tokenize args */
		num_of_arg = tokenize_input(buffer, args);

		/* for debugging */
		// printf("sizeof *args[i]: %zu\n", sizeof(args[0]));
		for (i = 0; i <= num_of_arg; i++) { 
			printf("Items of args[%d]: %s\n", i, args[i]);
			/* 
			 * %s needs string. In other words,
			 * it needs pointer to char
			 * Thus, not *args[i] but args[i]
			 */
		}
	}

	/* free memory */
	free(buffer);

	return 0;
}

/* 
 * is_blank_string:	if they are blank, then return 1
 * 			if they not, return 0
 */
int is_blank_string(char *buffer, size_t buff_size)
{
	for (int i = 0; i < buff_size; i++) {
		if (!isspace(buffer[i])) {
			return 0;
		}
	}
	return 1;
}

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
	} while (token = strtok(NULL, " "));

	args[i] = NULL; /* required for execvp(). What is this? */

	return num_of_arg;
}
