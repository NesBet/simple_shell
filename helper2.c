#include "main.h"

/**
 * help_helper - Help information about our help.
 *
 * Return: Nothing.
 */

void help_helper(void)
{
	char *help = "help: help [-dms] [pattern]\n";

	write(STDOUT_FILENO, help, str_len(help));
	help = "\tShows information about builtin commands.\n ";
	write(STDOUT_FILENO, help, str_len(help));
	help = "Shows short summaries of builtin commands.\n";
	write(STDOUT_FILENO, help, str_len(help));
}
/**
 * alias_helper - Help information about our alias.
 *
 * Return: Nothing.
 */

void alias_helper(void)
{
	char *help = "alias: alias [-p] [name[=value]]\n";

	write(STDOUT_FILENO, help, str_len(help));
	help = "\tDefine/show aliases.\n ";
	write(STDOUT_FILENO, help, str_len(help));
}

/**
 * cd_helper - Help information about our alias.
 *
 * Return: Nothing.
 */

void cd_helper(void)
{
	char *help = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, help, str_len(help));
	help = "\tChanges working valid directory.\n ";
	write(STDOUT_FILENO, help, str_len(help));
}
