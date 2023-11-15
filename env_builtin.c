/* env_builtin.c */
#include "shell.h"

/**
 * print_selected_environment - Print selected environment variables
 * Return: this returns void
 * @selected_vars: mn yagebaha
 */
void print_selected_environment(char *selected_vars[])
{
	int i = 0;

	while (selected_vars[i] != NULL)
	{
		char *value = getenv(selected_vars[i]);

		if (value != NULL)
		{
			write(STDOUT_FILENO, selected_vars[i], _strlen(selected_vars[i]));
			write(STDOUT_FILENO, "=", 1);
			write(STDOUT_FILENO, value, _strlen(value));
			write(STDOUT_FILENO, "\n", 1);
		}
		i++;
	}
}

/**
 * execute_env_command - Execute the /usr/bin/env command
 */
void execute_env_command(void)
{
	char *env_command = "/usr/bin/env";
	char **args; /* Declare args as a pointer to a pointer */
	pid_t child_pid;

	args = malloc(2 * sizeof(char *)); /* Allocate memory for args */
	args[0] = env_command;
	args[1] = NULL;

	child_pid = fork();
	if (child_pid == 0)
	{
		execve(env_command, args, NULL);
		perror("Execution error");
		_exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(child_pid, NULL, 0);
	}

	free(args); /* Don't forget to free args when you're done with it */
}

/**
 * print_environment - Print selected
 */
void print_environment(void)
{
	char *selected_vars[] = {
		"USER", "LANGUAGE", "SESSION", "COMPIZ_CONFIG_PROFILE", "SHLVL", "HOME",
		"C_IS", "DESKTOP_SESSION", "LOGNAME", "TERM", "PATH", "DISPLAY", NULL
	};

	print_selected_environment(selected_vars);
	execute_env_command();
}
