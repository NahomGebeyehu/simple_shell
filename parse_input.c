/* parse_input.c */
#include "shell.h"
#include <stdlib.h>
#include <string.h>  /* Add this line for the strtok function */

/**
 * parse_input - Tokenizes input into an array of strings
 * @input: User input
 *
 * Return: Array of strings
 */
char **parse_input(char *input)
{
char **tokens = NULL;
char *token;
int i = 0;

tokens = malloc(MAX_INPUT * sizeof(char *));
if (tokens == NULL)
{
	perror("malloc");
	_exit(EXIT_FAILURE);
}

token = strtok(input, " \t\n");
while (token != NULL)
{
	tokens[i++] = token;
	token = strtok(NULL, " \t\n");
}
	tokens[i] = NULL; /* Null-terminate the array */
	return (tokens);
}

