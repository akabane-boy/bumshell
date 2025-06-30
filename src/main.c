#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* declaration */
int is_blank_string(char *buffer, size_t buff_size);

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
	}

	/* free memory */
	free(buffer);

	return 0;
}

	/* 
	 * is_blank_string:	if they are blank, then return 1
	 *			if they not, return 0
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
