#include "main.h"

/**
 * index_first_char - Finds index of the first character.
 * @input: Input string.
 * @i: index.
 *
 * Return: 1 for error, 0 otherwise.
 */
int index_first_char(char *input, int *i)
{

	for (*i = 0; input[*i]; *i += 1)
	{
		if (input[*i] == ' ' || input[*i] == '\t')
			continue;
		if (input[*i] == ';' || input[*i] == '|' || input[*i] == '&')
			return (-1);
		break;
	}
	return (0);
}

/**
 * rpt_char - Counts character repetitions.
 * @input: Input string.
 * @i: Index.
 *
 * Return: Repetitions.
 */
int rpt_char(char *input, int i)
{
	if (*(input - 1) == *input)
		return (rpt_char(input - 1, i + 1));
	return (i);
}

/**
 * syntax_err - Finds syntax errors.
 * @input: Input string.
 * @i: Index.
 * @lst: Last character.
 *
 * Return: Index of error, 0 if none.
 */
int syntax_err(char *input, int i, char lst)
{
	int count;

	count = 0;
	if (*input == '\0')
		return (0);
	if (*input == ' ' || *input == '\t')
		return (syntax_err(input + 1, i + 1, lst));

	if (*input == ';')
		if (lst == '|' || lst == '&' || lst == ';')
			return (i);

	if (*input == '|')
	{
		if (lst == ';' || lst == '&')
			return (i);

		if (lst == '|')
		{
			count = rpt_char(input, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	if (*input == '&')
	{
		if (lst == ';' || lst == '|')
			return (i);
		if (lst == '&')
		{
			count = rpt_char(input, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	return (syntax_err(input + 1, i + 1, *input));
}

/**
 * print_syntax_err - Prints a syntax error.
 * @datastruct: Data structure.
 * @input: Input string.
 * @i: Error index.
 * @bool: Controls error.
 *
 * Return: Nothing.
 */
void print_syntax_err(shell_info *datastruct, char *input, int i, int bool)
{
	char *mssg1, *mssg2, *mssg3, *error, *count;
	int size;

	if (input[i] == ';')
	{
		if (bool == 0)
			mssg1 = (input[i + 1] == ';' ? ";;" : ";");
		else
			mssg1 = (input[i - 1] == ';' ? ";;" : ";");
	}

	if (input[i] == '|')
		mssg1 = (input[i + 1] == '|' ? "||" : "|");

	if (input[i] == '&')
		mssg1 = (input[i + 1] == '&' ? "&&" : "&");

	mssg2 = "Syntax error \"";
	mssg3 = "\" Unexpected error\n";
	count = conv_str(datastruct->count);
	size = str_len(datastruct->av[0]) + str_len(count);
	size += str_len(mssg1) + str_len(mssg2) + str_len(mssg3) + 2;

	error = malloc(sizeof(char) * (size + 1));
	if (error == 0)
	{
		free(count);
		return;
	}
	str_copy(error, datastruct->av[0]);
	str_cat(error, ": ");
	str_cat(error, count);
	str_cat(error, mssg2);
	str_cat(error, mssg1);
	str_cat(error, mssg3);
	str_cat(error, "\0");

	write(STDERR_FILENO, error, size);
	free(error);
	free(count);
}

/**
 * check_syntax_err - Checks and prints an error.
 * @datastruct: Data structure.
 * @input: Input string.
 *
 * Return: 1 for error, 0 otherwise.
 */
int check_syntax_err(shell_info *datastruct, char *input)
{
	int a = 0;
	int start = 0;
	int final = 0;

	final = index_first_char(input, &start);
	if (final == -1)
	{
		print_syntax_err(datastruct, input, start, 0);
		return (1);
	}

	a = syntax_err(input + start, 0, *(input + start));
	if (a != 0)
	{
		print_syntax_err(datastruct, input, start + a, 1);
		return (1);
	}

	return (0);
}
