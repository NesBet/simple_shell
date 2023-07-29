#include "main.h"

/**
 * env_helper - Helper information about our environent.
 *
 * Return: Nothing.
 */

void env_helper(void)
{
	char *help = "env: env [opton] [name=value] [command [args]]\n\t";

	write(STDOUT_FILENO, help, str_len(help));
	help = "Print environments shell.\n";
	write(STDOUT_FILENO, help, str_len(help));
}

/**
 * setenv_helper - Helper information about our setenv.
 *
 * Return: Nothing.
 */

void setenv_helper(void)
{
	char *help = "setenv: setenv (const char *name), const char *value,";

	write(STDOUT_FILENO, help, str_len(help));
	help = "Replaceable int\n\t";
	write(STDOUT_FILENO, help, str_len(help));
	help = "Add new definition to environment\n";
	write(STDOUT_FILENO, help, str_len(help));
}

/**
 * unsetenv_helper - Helper information about our unsetenv.
 *
 * Return: Nothing.
 */

void unsetenv_helper(void)
{
	char *help = "unsetenv: unsetenv (const char *name)\n\t";

	write(STDOUT_FILENO, help, str_len(help));
	help = "Delete an entry from the environment\n";
	write(STDOUT_FILENO, help, str_len(help));
}

/**
 * general_helper - Entry for our builtin help.
 *
 * Return: Nothing.
 */
void general_helper(void)
{
	char *help = "($) bash,\n";

	write(STDOUT_FILENO, help, str_len(help));
	help = "Some commands are defined internally.Use 'help' to see the list.";
	write(STDOUT_FILENO, help, str_len(help));
	help = "Use 'help name' to learn more about the function 'name'.\n\n ";
	write(STDOUT_FILENO, help, str_len(help));
	help = " alias: alias [name=['string']]\n cd: cd [-L|[-P [-e]] [-@]] ";
	write(STDOUT_FILENO, help, str_len(help));
	help = "[dir]\nexit: exit [n]\n  env: env [option] [name=value] [command ";
	write(STDOUT_FILENO, help, str_len(help));
	help = "[args]]\n  setenv: setenv [variable] [value]\n  unsetenv: ";
	write(STDOUT_FILENO, help, str_len(help));
	help = "unsetenv [variable]\n";
	write(STDOUT_FILENO, help, str_len(help));
}

/**
 * exit_helper - Help info about our exit.
 *
 * Return: Nothing.
 */

void exit_helper(void)
{
	char *help = "exit: exit [n]\n Exit shell.\n";

	write(STDOUT_FILENO, help, str_len(help));
	help = "Exits shell with a status of n, just exits if n is ommitted";
	write(STDOUT_FILENO, help, str_len(help));
	help = "Status of last command executed\n";
	write(STDOUT_FILENO, help, str_len(help));
}

