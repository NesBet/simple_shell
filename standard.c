#include "main.h"

/**
 * len_no - Length of a number.
 * @n: Number.
 *
 * Return: Length of the number.
 */

int len_no(int n)
{
	int length = 1;
	unsigned int n2;

	if (n < 0)
	{
		length++;
		n2 = n * -1;
	}
	else
	{
		n2 = n;
	}
	while (n2 > 9)
	{
		length++;
		n2 = n2 / 10;
	}

	return (length);
}

/**
 * conv_str - Converts an integer into strng.
 * @n: Integer.
 *
 * Return: String.
 */

char *conv_str(int n)
{
	unsigned int n2;
	int length = len_no(n);
	char *buffer;

	buffer = malloc(sizeof(char) * (length + 1));
	if (buffer == 0)
		return (NULL);
	*(buffer + length) = '\0';

	if (n < 0)
	{
		n2 = n * -1;
		buffer[0] = '-';
	}
	else
	{
		n2 = n;
	}
	length--;
	do {
		*(buffer + length) = (n2 % 10) + '0';
		n2 = n2 / 10;
		length--;
	}
	while (n2 > 0)
		;
	return (buffer);
}

/**
 * conv_int - Converts s string to an integer.
 * @s: String.
 *
 * Return: Integer.
 */

int conv_int(char *s)
{
	unsigned int count = 0, size = 0, a = 0, b = 1, c = 1, i;

	while (*(s + count) != '\0')
	{
		if (size > 0 && (*(s + count) < '0' || *(s + count) > '9'))
			break;
		if ((*(s + count) >= '0') && (*(s + count) <= '9'))
		{
			if (size > 0)
				c *= 0;
			size++;
		}
		count++;
	}
	for (i = count - size; i < count; i++)
	{
		a = a + ((*(s + i) - 48) * c);
		c /= 10;
	}
	return (a * b);
}
