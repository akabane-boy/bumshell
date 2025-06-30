#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h> /* For fork() */
#include <sys/wait.h> /* For wait() */

/* declaration */
int is_blank_string(char *buffer, size_t buff_size);
int tokenize_input(char *buffer, char **args);

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
		 * FROM HERE: dealing with input string 
		 */

		char *args[32]; /* array of pointers */
		int num_of_arg;

		/*
		 * tokenize the user input based on spaces
		 */
		num_of_arg = tokenize_input(buffer, args);


		/* 
		 * TODO: Deals with token
		 */

		pid_t pid;

		pid = fork(); 
		/* 
		 * creates child process which is completely same to
		 * parents process.
		 */

		/* From here, parallel world begins. */
		if (pid == -1) {
			perror("fork failed");
			continue;
		} else if (pid == 0) { 
			/* This code runs in the child process */
			printf("Child process started!: PID = %d\n", getpid());
			execvp(args[0], args); /* execute args[o] followed by args */

			/* 
			 * By execvp() function, child process gets replaced by new program
			 * that specified in execvp()'s argument.
			 * So, if program that is replaced by execvp successfully ends,
			 * then child process successfully ends.
			 */

			/* execvp only returns if an error occurs */
			perror("execvp failed"); /* This line is reached only on error */
			exit(EXIT_FAILURE);
		} else {
			/* This code runs in the parent process */
			wait(NULL); /* Wait for the child process to complete */
			printf("Child process done!\n");
			printf("Now Parent process started!: PID = %d\n", getpid());
		}

		printf("Done forking.\nNow: PID = %d\n", getpid()); /* Both parent and child execute this */

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

	args[i] = NULL; /* required for execvp(). */

	return num_of_arg;
}
