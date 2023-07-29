#include "main.h"

/**
 * cd_action -Changes active directory.
 * @datastruct: Relevant data.
 *
 * Return: 1 for successful execution.
 */

int cd_action(shell_info *datastruct)
{
	char *dir;
	int check, check2, dash;

	dir = datastruct->args[1];

	if (dir != NULL)
	{
		check = str_comp("$HOME", dir);
		check2 = str_comp("~", dir);
		dash = str_comp("--", dir);
	}

	if (dir == NULL || !check || !check2 || !dash)
	{
		cd_home(datastruct);
		return (1);
	}

	if (str_comp("-", dir) == 0)
	{
		cd_previous(datastruct);
		return (1);
	}

	if (str_comp(".", dir) == 0 || str_comp("..", dir) == 0)
	{
		cd_par(datastruct);
		return (1);
	}

	cd_to(datastruct);
	return (1);
}
