#include "main.h"

/**
 * free_struct - Frees data structure.
 * @datastruct: Data structure.
 *
 * Return: Nothing.
 */
void free_struct(shell_info *datastruct)
{
	unsigned int n;

	for (n = 0; datastruct->our_environ[n]; n++)
	{
		free(datastruct->our_environ[n]);
	}
	free(datastruct->our_environ);
	free(datastruct->pid);
}

/**
 * set_struct - Initialize data structure.
 * @datastruct: The data structure.
 * @av: Argument vector.
 *
 * Return: Nothing.
 */
void set_struct(shell_info *datastruct, char **av)
{
	unsigned int i;

	datastruct->av = av;
	datastruct->command = NULL;
	datastruct->args = NULL;
	datastruct->status = 0;
	datastruct->count = 1;

	for (i = 0; environ[i]; i++)
		;
	datastruct->our_environ = malloc(sizeof(char *) * (i + 1));
	for (i = 0; environ[i]; i++)
	{
		datastruct->our_environ[i] = str_dup(environ[i]);
	}
	datastruct->our_environ[i] = NULL;
	datastruct->pid = conv_str(getpid());
}

/**
 * main - Entry.
 * @ac: Argument count.
 * @av: Argument vector.
 *
 * Return: 0 on success.
 */

int main(int ac, char **av)
{
	shell_info datastruct;
	(void) ac;

	signal(SIGINT, get_signature);
	set_struct(&datastruct, av);
	shell_loop(&datastruct);
	free_struct(&datastruct);
	if (datastruct.status < 0)
		return (255);
	return (datastruct.status);
}
