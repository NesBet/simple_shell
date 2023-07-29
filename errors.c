#include "main.h"

/**
 * get_error - Calls the error accordingly.
 * @datastruct: Data structure.
 * @errval: Error value.
 *
 * Return: Error.
 */

int get_error(shell_info *datastruct, int errval)
{
	char *error;

	switch (errval)
	{
	case -1:
		error = environ_err(datastruct);
		break;
	case 2:
		if (str_comp("exit", datastruct->args[0]) == 0)
			error = shell_exit(datastruct);
		else if (str_comp("cd", datastruct->args[0]) == 0)
			error = error_cd(datastruct);
		break;
	case 126:
		error = error_path(datastruct);
		break;
	case 127:
		error = error_not_found(datastruct);
		break;
	}
	if (error)
	{
		write(STDERR_FILENO, error, str_len(error));
		free(error);
	}
	datastruct->status = errval;
	return (errval);
}
