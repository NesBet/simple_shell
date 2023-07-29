#include "main.h"

/**
 * get_builtin - Builtin commands pairing.
 * @cmd: A command.
 *
 * Return: Pointer of builtin command.
 */
int (*get_builtin(char *cmd))(shell_info *datastruct)
{
	builtin_t builtin[] = {
		{ "env", print_env },
		{ "exit", exit_shell },
		{ "setenv", set_environ },
		{ "unsetenv", del_set_environ },
		{ "cd", cd_action },
		{ "help", get_help },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; builtin[i].name; i++)
	{
		if (str_comp(builtin[i].name, cmd) == 0)
			break;
	}
	return (builtin[i].f);
}
