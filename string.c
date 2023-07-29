#include "main.h"

/**
 * str_cat - Concatenantes 2 strings.
 * @dest: Destination pointer of copied string.
 * @src: Pointer to source of string.
 *
 * Return: Destination.
 */

char *str_cat(char *dest, const char *src)
{
	int a;
	int b;

	for (a = 0; dest[a] != '\0'; a++)
		;
	for (b = 0; src[b] != '\0'; b++)
	{
		dest[a] = src[b];
		a++;
	}
	dest[a] = '\0';
	return (dest);
}

/**
 * str_copy - Copies string pointed by the source.
 * @src: Pointer of source string.
 * @dest: Pointer to copied string.
 *
 * Return: Destination.
 */

char *str_copy(char *dest, char *src)
{
	size_t a;

	for (a = 0; src[a] != '\0'; a++)
	{
		dest[a] = src[a];
	}
	dest[a] = '\0';

	return (dest);
}

/**
 * str_comp - Compares two strings.
 * @st1: String 1.
 * @st2: String 2.
 *
 * Return: 0.
 */

int str_comp(char *st1, char *st2)
{
	int a;

	for (a = 0; st1[a] == st2[a] && st1[a]; a++)
		;
	if (st1[a] > st2[a])
		return (1);
	if (st1[a] < st2[a])
		return (-1);
	return (0);
}

/**
 * str_char - Finds character in string.
 * @st: String.
 * @ch: Character.
 *
 * Return: Pointer to first encounter of character.
 */

char *str_char(char *st, char ch)
{
	unsigned int a = 0;

	for (; *(st + a) != '\0'; a++)
		if (*(st + a) == ch)
			return (st + a);

	if (*(st + a) == ch)
		return (st + a);
	return ('\0');
}

/**
 * str_spin - Obtains length of prefix.
 * @seg: Initial segment.
 * @acc: Accepted number of bytes.
 *
 * Return: Number of accepted bytes.
 */

int str_spin(char *seg, char *acc)
{
	int bool, a, b;

	for (a = 0; *(seg + a) != '\0'; a++)
	{
		bool = 1;
		for (b = 0; *(acc + b) != '\0'; b++)
		{
			if (*(seg + a) == *(acc + b))
			{
				bool = 0;
				break;
			}
		}
		if (bool == 1)
			break;
	}
	return (a);
}
