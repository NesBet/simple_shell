#include "main.h"


/**
 * read_line - Reads the input string.
 * @rtn: Return value.
 *
 * Return: Input string
 */
char *read_line(int *rtn)
{
	char *input = NULL;
	size_t bufsize = 0;

	*rtn = getline(&input, &bufsize, stdin);
	return (input);
}
