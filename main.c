#include "shell.h"

/**
 * main - This function is an entry point of the simple shell
 * @ac: This is the number of command line arguments
 * @av: this is an array containing the command line arguments
 *
 * Return: This returns 0
 */
int main(int ac, char **av)
{
	(void)ac;
	(void)av;

	if (isatty(STDIN_FILENO))
	return (run_simple_shell(1));
else
	return (run_simple_shell(0));
}
