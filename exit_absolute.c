#include "shell.h"

/**
 * is_absolute_path - Check if a path is absolute.
 * @path: The path to check.
 *
 * Return: 1 if the path is absolute, 0 otherwise.
 */
int is_absolute_path(const char *path)
{
	return (path[0] == '/');
}

/**
 * exit_shell - Exit the shell.
 */
void exit_shell(void)
{
	char *buffer = NULL;

	free(buffer);
	exit(EXIT_SUCCESS);
}
