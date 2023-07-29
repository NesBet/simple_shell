#include "main.h"

/**
 * obtain_line - Assignment operator.
 * @buffline: Buffer storing input string.
 * @buffer: String called to buffer.
 * @n: Line size.
 * @j: Buffer size.
 */
void obtain_line(char **buffline, size_t *n, char *buffer, size_t j)
{

	if (*lineptr == NULL)
	{
		if  (j > BUFSIZE)
			*n = j;
		else
			*n = BUFSIZE;
		*buffline = buffer;
	}
	else if (*n < j)
	{
		if (j > BUFSIZE)
			*n = j;
		else
			*n = BUFSIZE;
		*buffline = buffer;
	}
	else
	{
		str_copy(*buffline, buffer);
		free(buffer);
	}
}
/**
 * get_line - Read input from stream.
 * @buffline: Buffer.
 * @n: Size.
 * @stream: Streaming point.
 *
 * Return: Bytes.
 */
ssize_t get_line(char **buffline, size_t *n, FILE *stream)
{
	ssize_t retrival;
	int i;
	char *buffer;
	char t = 'z';
	static ssize_t input;

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * BUFSIZE);
	if (buffer == 0)
		return (-1);
	while (t != '\n')
	{
		i = read(STDIN_FILENO, &t, 1);
		if (i == -1 || (i == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (i == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= BUFSIZE)
			buffer = mem_realloc(buffer, input, input + 1);
		buffer[input] = t;
		input++;
	}
	buffer[input] = '\0';
	obtain_line(buffline, n, buffer, input);
	retrival = input;
	if (i != 0)
		input = 0;
	return (retrival);
}
