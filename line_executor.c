#include "main.h"

/**
 * line_executor - Handles built-in commands.
 * @datastruct: Required data.
 *
 * Return: 1 on success.
 */
int line_executor(shell_info *datastruct)
{
	int (*builtin)(shell_info *datastruct);

	if (datastruct->args[0] == NULL)
		return (1);
	builtin = get_builtin(datastruct->args[0]);
	if (builtin != NULL)
		return (builtin(datastruct));

	return (cmd(datastruct));
}
