#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h> /* For fork() */
#include <sys/wait.h> /* For wait() */
/* Own headers! */
#include "../include/input.h" /* is_blank_string() */
#include "../include/parser.h" /* tokenize_input */
#include "../include/executor.h" /* execute_command */
#include "../include/builtins.h" /* built-ins */

int main(void)
{
	char *buffer = NULL;
	size_t buff_size = 0;
	int characters;
	size_t input_len;

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
		if (is_blank_string(buffer, input_len)) continue;

		/* 
		 * FROM HERE: dealing with input string 
		 */

		char *args[32]; /* array of pointers */

		/*
		 * tokenize the user input based on spaces
		 */
		tokenize_input(buffer, args);

		/*
		 * handles built-in commands!
		 */
		if (built_in(args) == 1) continue;

		/* executing command via fork and execvp */
		execute_command(args);

	}

	/* free memory */
	free(buffer);

	return 0;
}

