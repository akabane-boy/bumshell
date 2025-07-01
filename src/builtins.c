#include "../include/builtins.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int built_in(char **args)
{
	/*
	 * built-in commands!
	 * Returns 1 if any of commands executed
	 * Returns 0 if none of commands executed
	 */

	/* **************** pwd *************************
	 * cd [dir]
	 */
	if (strcmp(args[0], "cd") == 0) {
		if (chdir(args[1]) == 0);
		else perror("Failed to change directory");
		return 1;
	}

	/* **************** pwd *************************
	 * Even though, execute_commands can handle "pwd",
	 * I just re-implemented for my learning.
	 */
	char *pwd = NULL;
	if (strcmp(args[0], "pwd") == 0) {
		if ((pwd = getcwd(pwd, 0)) != NULL) {
			printf("Current dir: %s\n", pwd);
			free(pwd);
			return 1;
		} else {
			perror("getcwd error");
		} 
	}

	/* **************** pwd *************************
	 * exit bumshell when "exit" typed
	 */
	if (strcmp(args[0], "exit") == 0) {
		exit(EXIT_SUCCESS);
	}

	return 0; /* None of the built-in commands executed */
}
