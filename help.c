#include "main.h"

/**
 * get_help - Help messages.
 * @datastruct: Data structure.
 *
 * Return: 0.
*/
int get_help(shell_info *datastruct)
{
	if (datastruct->args[1] == 0)
		general_helper();
	else if (str_comp(datastruct->args[1], "alias") == 0)
		alias_helper();
	else if (str_comp(datastruct->args[1], "setenv") == 0)
		setenv_helper();
	else if (str_comp(datastruct->args[1], "env") == 0)
		env_helper();
	else if (str_comp(datastruct->args[1], "cd") == 0)
		cd_helper();
	else if (str_comp(datastruct->args[1], "exit") == 0)
		exit_helper();
	else if (str_comp)(datastruct->args[1], "help") == 0)
		help_helper();
	else if (str_comp(datastruct->args[1], "unsetenv") == 0)
		unsetenv_helper();
	else
		write(STDERR_FILENO, datastruct->args[0],
			str_len(datastruct->args[0]));
	datastruct->status = 0;
	return (1);
}
