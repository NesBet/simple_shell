#include "main.h"

/**
 * rev_str - Reverses a string.
 * @st: Input string.
 *
 * Return: Nothing.
 */

void rev_str(char *st)
{
	int count = 0;
	int a, b;
	char *string, tempo;

	while (count >= 0)
	{
		if (st[count] == '\0')
			break;
		count++;
	}
	string = st;

	for (a = 0; a < (count - 1); a++)
	{
		for (b = a + 1; b > 0; b--)
		{
			tempo = *(string + b);
			*(string + b) = *(string + (b - 1));
			*(string + (b - 1)) = tempo;
		}
	}
}
