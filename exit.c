#include "main.h"

/**
 * exit_shell - Leaves shel.
 * @datastruct: Data.
 *
 * Return: 0 on success.
 */
int exit_shell(shell_info *datastruct)
{
	unsigned int stts;
	int digit;
	int big_no;
	int strlen;

	if (datastruct->args[1] != NULL)
	{
		stts = conv_int(datastruct->args[1]);
		digit = is_digit(datastruct->args[1]);
		strlen = str_len(datastruct->args[1]);
		big_no = stts > (unsigned int)INT_MAX;
		if (!is_digit || strlen > 10 || big_no)
		{
			find_error(datastruct, 2);
			datastruct->status = 2;
			return (1);
		}
		datastruct->status = (stts % 256);
	}
	return (0);
}
