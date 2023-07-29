#include "main.h"

/**
 * delete_comment - Deletes comments from the input.
 * @in: Input string.
 *
 * Return: Input without comments.
 */
char *delete_comment(char *in)
{
	int i, upto;

	upto = 0;
	for (i = 0; in[i]; i++)
	{
		if (in[i] == '#')
		{
			if (i == 0)
			{
				free(in);
				return (NULL);
			}

			if (in[i - 1] == ' ' || in[i - 1] == '\t' || in[i - 1] == ';')
				upto = i;
		}
	}

	if (upto != 0)
	{
		in = mem_realloc(in, i, upto + 1);
		in[upto] = '\0';
	}
	return (in);
}

/**
 * shell_loop - Loop for running shell.
 * @datastruct: Arguments.
 *
 * Return: Nothing.
 */

void shell_loop(shell_info *datastruct)
{
	int loop, rtn;
	char *input;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, "($) ", 4);
		input = read_line(&rtn);
		if (rtn != -1)
		{
			input = delete_comment(input);
			if (input == NULL)
				continue;

			if (check_syntax_err(datastruct, input) == 1)
			{
				datastruct->status = 2;
				free(input);
				continue;
			}
			input = rep_var(input, datastruct);
			loop = split_commands(datastruct, input);
			datastruct->count += 1;
			free(input);
		}
		else
		{
			loop = 0;
			free(input);
		}
	}
}
