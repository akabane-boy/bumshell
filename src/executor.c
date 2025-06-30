#include "../include/executor.h" /* own header */
#include <stdio.h> /* For perror() */
#include <stdlib.h> /* For exit() */
#include <unistd.h> /* For fork() */
#include <sys/wait.h> /* For wait() */

void execute_command(char **args)
{
	/* Deals with token */
	pid_t pid;

	pid = fork(); 
	/* 
	 * fork() creates child process which is completely same to
	 * parents process.
	 */

	/* From here, parallel world begins. */
	if (pid == -1) {
		perror("fork failed");
		exit(EXIT_FAILURE);
	} else if (pid == 0) { 
		/* This code runs in the child process */
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
	}
}
