#include "main.h"

/**
 * environ_comp - Compares names of environments.
 * @envname: Environment name variable.
 * @name: Name passed.
 *
 * Return: 0 if not equal, else if equal.
 */
int environ_comp(const char *envname, const char *name)
{
	int a;

	for (a = 0; envname[a] != '='; a++)
	{
		if (envname[a] != name[a])
		{
			return (0);
		}
	}

	return (a + 1);
}

/**
 * get_env - Obtains environment variable.
 * @name: Name of environment variable.
 * @our_environ: Environament variable.
 *
 * Return: Value of environment variable if present.
 */
char *get_env(const char *name, char **our_environ)
{
	char *ptr;
	int i, move;

	ptr = NULL;
	move = 0;

	for (i = 0; our_environ[i]; i++)
	{
		move = environ_comp(our_environ[i], name);
		if (move)
		{
			ptr = our_environ[i];
			break;
		}
	}
	return (ptr + move);
}

/**
 * print_env - Prints the evironment variables.
 * @datastruct: Data structure.
 *
 * Return: 1 on success.
 */
int print_env(shell_info *datastruct)
{
	int a, b;

	for (a = 0; datastruct->our_environ[a]; a++)
	{

		for (b = 0; datastruct->our_environ[a][b]; b++)
			;
		write(STDOUT_FILENO, datastruct->our_environ[a], b);
		write(STDOUT_FILENO, "\n", 1);
	}
	datastruct->status = 0;
	return (1);
}
