#include "shell.h"
#include <stdlib.h>

int is_absolute_path(const char *path);

/**
 * set_environment_variable - Set or modify an environment variable
 * @args: Arguments passed to the setenv command
 * Return: 0 on success, -1 on failure
 */
int set_environment_variable(char **args)
{
	if (args[1] == NULL || args[2] == NULL || args[3] != NULL)
	{
		fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
		return (-1);
	}

	if (setenv(args[1], args[2], 1) == -1)
	{
		perror("setenv");
		return (-1);
	}

	return (0);
}

/**
 * unset_environment_variable - Unset an environment variable
 * @args: Arguments passed to the unsetenv command
 * Return: 0 on success, -1 on failure
 */
int unset_environment_variable(char **args)
{
	if (args[1] == NULL || args[2] != NULL)
	{
		fprintf(stderr, "Usage: unsetenv VARIABLE\n");
		return (-1);
	}

	if (unsetenv(args[1]) == -1)
	{
		perror("unsetenv");
		return (-1);
	}

	return (0);
}

/**
 * execute_command - Execute a command
 * @args: Arguments passed to the command
 */
void execute_command(char **args)
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error forking");
	}
	else if (child_pid == 0)
	{
		/* Child process */
		if (execve(args[0], args, NULL) == -1)
		{
			perror("Execution error");
			_exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* Parent process */
		waitpid(child_pid, &status, 0);
	}
}

/**
 * run_simple_shell - Runs a simple shell
 * @interactive: Flag to check if shell is interactive
 * Return: 0 on success
 */
int run_simple_shell(int interactive)
{
	char *buffer = NULL;
	ssize_t characters;
	char *path;
	size_t len = 0;

	path = getenv("PATH");

	signal(SIGINT, SIG_IGN);

	while (1)
	{
		char **args;

		if (interactive)
			write(STDOUT_FILENO, "$ ", 2);

		characters = getline(&buffer, &len, stdin);

		if (characters == -1)
		{
			if (interactive && isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			free(buffer);
			exit_shell();
		}

		buffer[characters - 1] = '\0'; /* Remove newline character */

		if (buffer[0] == '#' &&
		 (buffer[1] == ' ' || buffer[1] == '\t' || buffer[1] == '\0'))
		{
			free(buffer);
			continue;
		}
		if (characters > 1) /* Ignore empty lines */
		{
			args = parse_input(buffer);

			if (_strcmp(args[0], "exit") == 0)
			{
				free(buffer);
				free(args);
				exit_shell();
			}
			else if (_strcmp(args[0], "env") == 0)
			{
				print_environment();
			}
			else if (_strcmp(args[0], "setenv") == 0)
			{
				set_environment_variable(args);
			}
			else if (_strcmp(args[0], "unsetenv") == 0)
			{
				unset_environment_variable(args);
			}
			else if (!is_absolute_path(args[0]))
			{
				char *full_path = search_path(args[0], path);

				if (full_path != NULL)
				{
					args[0] = full_path;
				}
				else
				{
					if (interactive)
					{
						write(STDERR_FILENO, "shell: ", 8);
						write(STDERR_FILENO, args[0], _strlen(args[0]));
						write(STDERR_FILENO, ": not found\n", 12);
					}
					free(args);
					continue;
				}
			}

			execute_command(args);

			free(args);
		}
	}
	free(buffer);
	return (0);
}

