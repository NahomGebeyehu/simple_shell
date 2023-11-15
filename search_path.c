/* search_path.c */
#include "shell.h"
#include <stdlib.h>

char *create_full_path(char *token, char *command, size_t token_len);
char *check_path(char *token, char *command);

/**
 * search_path - This searchs for the command in the PATH directories
 * @command: This is the command to search for
 * @path: This is the PATH environment variable
 * Return: Full path to the command if found, NULL otherwise
 */
char *search_path(char *command, char *path)
{
	char *token, *full_path;
	char *path_copy = NULL;
	size_t path_len, i;

	path_len = _strlen(path);

	path_copy = malloc(path_len + 1);
	if (path_copy == NULL)
	{
		perror("malloc");
		_exit(EXIT_FAILURE);
	}

	for (i = 0; i < path_len; i++)
		path_copy[i] = path[i];
	path_copy[i] = '\0';

	token = path_copy;

	while (*token != '\0')
	{
		full_path = check_path(token, command);
		if (full_path != NULL)
		{
			free(path_copy);
			return (full_path);
		}

		while (*token != '\0' && *token != ':' && *token != '\n')
			token++;

		if (*token == ':' || *token == '\n')
			token++;
	}

	free(path_copy);
	return (NULL);
}

/**
 * check_path - Checks if the command exists in the path
 * @token: The path to check
 * @command: The command to search for
 * Return: Full path to the command if found, NULL otherwise
 */
char *check_path(char *token, char *command)
{
	char *full_path;
	size_t token_len = 0;

	while (token[token_len] != '\0' &&
	token[token_len] != ':' &&
	token[token_len] != '\n')

		token_len++;

	full_path = create_full_path(token, command, token_len);

	if (access(full_path, F_OK | X_OK) == 0)
		return (full_path);

	free(full_path);
	return (NULL);
}

/**
 * create_full_path - Creates the full path of the command
 * @token: The path
 * @command: The command
 * @token_len: The length of the path
 * Return: The full path of the command
 */
char *create_full_path(char *token, char *command, size_t token_len)
{
	char *full_path;
	size_t full_path_len, i, j;

	full_path_len = token_len + _strlen(command) + 2;
	full_path = malloc(full_path_len);
	if (full_path == NULL)
	{
		perror("malloc");
		_exit(EXIT_FAILURE);
	}

	for (i = 0; i < token_len; i++)
		full_path[i] = token[i];

	full_path[i] = '/';
	i++;

	for (j = 0; j < _strlen(command); j++, i++)
		full_path[i] = command[j];

	full_path[i] = '\0';

	return (full_path);
}

