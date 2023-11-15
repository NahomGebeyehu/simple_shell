#include "shell.h"
#include <unistd.h>

void print_environment(void)
{
char *selected_vars[] = {
	"USER",
	"LANGUAGE",
	"SESSION",
	"COMPIZ_CONFIG_PROFILE",
	"SHLVL",
	"HOME",
	"C_IS",
	"DESKTOP_SESSION",
	"LOGNAME",
	"TERM",
	"PATH",
	"DISPLAY",
	NULL
};

int i = 0;
while (selected_vars[i] != NULL)
{
	char *value = getenv(selected_vars[i]);

if (value != NULL)
{
		write(STDOUT_FILENO, selected_vars[i], _strlen(selected_vars[i]));
		write(STDOUT_FILENO, "=", 1);
		write(STDOUT_FILENO, value, strlen(value));
		write(STDOUT_FILENO, "\n", 1);
}
	i++;
}
}

