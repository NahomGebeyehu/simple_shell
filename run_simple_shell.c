/* run_simple_shell.c */
#include "shell.h"
#include <stdlib.h>

int is_absolute_path(const char *path);

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
		pid_t child_pid;
		int status;

		if (interactive)
			write(STDOUT_FILENO, ":) ", 3);

		characters = getline(&buffer, &len, stdin);

		if (characters == -1)
		{
			if (interactive && isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			free(buffer);
			exit_shell();
		}

		buffer[characters - 1] = '\0'; /* Remove newline character */

		if (characters > 1) /* Ignore empty lines */
		{
			args = parse_input(buffer);

			if (_strcmp(args[0], "exit") == 0)
			{
				free(args);
				exit_shell();
			}
			else if (_strcmp(args[0], "env") == 0)
			{
				print_environment();
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
						write(STDERR_FILENO, "sh: 1: ", 6);
						write(STDERR_FILENO, args[0], _strlen(args[0]));
						write(STDERR_FILENO, ": not found\n", 12);
					}
					free(args);
					continue;
				}
			}

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

			free(args);
		}
	}

	return (0);
}

