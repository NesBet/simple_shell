#include "main.h"

/**
 * str_dup - Duplictes a string in heap.
 * @st: Char pointer to string.
 *
 * Return: Duplicated string.
 */

char *str_dup(const char *st)
{
	char *new;
	size_t len;

	len = str_len(st);
	new = malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	mem_copy(new, st, len + 1);
	return (new);
}

/**
 * str_len - Obtains lengthof a string.
 * @st: Char pointer.
 *
 * Return: 0.
 */

int str_len(const char *st)
{
	int len;

	for (len = 0; st[len] != 0; len++)
	{
	}
	return (len);
}

/**
 * chars_comp - Compares characters of strings.
 * @st: Input string.
 * @delim: A delimeter.
 *
 * Return: 1 if equal, 0 otherwise.
 */

int chars_comp(char st[], const char *delim)
{
	unsigned int a, b, c;

	for (a = 0, c = 0; st[a]; a++)
	{
		for (b = 0; delim[b]; b++)
		{
			if (st[a] == delim[b])
			{
				c++;
				break;
			}
		}
	}
	if (a == c)
		return (1);
	return (0);
}

/**
 * str_tok - Splits a string by delimeter specified.
 * @st: Input string.
 * @delim: Delimeter.
 *
 * Return: Splitted string.
 */

char *str_tok(char st[], const char *delim)
{
	static char *splitted, *st_end;
	char *st_start;
	unsigned int a, bool;

	if (st != NULL)
	{
		if (chars_comp(st, delim))
			return (NULL);
		splitted = st;
		a = str_len(st);
		st_end = &st[a];
	}
	st_start = splitted;
	if (st_start == st_end)
		return (NULL);

	for (bool = 0; *splitted; splitted++)
	{
		if (splitted != st_start)
			if (*splitted && *(splitted - 1) == '\0')
				break;
		for (a = 0; delim[a]; a++)
		{
			if (*splitted == delim[a])
			{
				*splitted = '\0';
				if (splitted == st_start)
					st_start++;
				break;
			}
		}
		if (bool == 0 && *splitted)
			bool = 1;
	}
	if (bool == 0)
		return (NULL);
	return (st_start);
}

/**
 * is_digit - Checks if string passed is a number.
 * @st: Input string.
 *
 * Return: 1 if string, 0 otherwise.
 */

int is_digit(const char *st)
{
	unsigned int a;

	for (a = 0; st[a]; a++)
	{
		if (st[a] < 48 || st[a] > 57)
			return (0);
	}
	return (1);
}
