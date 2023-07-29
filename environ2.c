#include "main.h"

/**
 * cote_enas - Copies information.
 * @name: Name
 * @value: Value
 *
 * Return: New environ or alias.
 */
char *cote_enas(char *name, char *value)
{
	char *new;
	int size_name, size_value, size;

	size_name = str_len(name);
	size_value = str_len(value);
	size = size_name + size_value + 2;
	new = malloc(sizeof(char) * (size));
	str_copy(new, name);
	str_cat(new, "=");
	str_cat(new, value);
	str_cat(new, "\0");
	return (new);
}

/**
 * set_environ - Sets an environment variable.
 * @name: Name of environment variable.
 * @value: Value of the environment variable.
 * @datastruct: Data structure.
 *
 * Return: Nothing.
 */

void set_environ(char *name, char *value, shell_info *datastruct)
{
	int a;
	char *env_var, *env_name;

	for (a = 0; datastruct->our_environ[a]; a++)
	{
		env_var = str_dup(datastruct->our_environ[a]);
		env_name = str_tok(env_var, "=");
		if (str_comp(env_name, name) == 0)
		{
			free(datastruct->our_environ[a]);
			datastruct->our_environ[a] = cote_enas(env_name, value);
			free(env_var);
			return;
		}
		free(env_var);
	}
	datastruct->our_environ =
		dpmem_realloc(datastruct->our_environ, a, sizeof(char *) * (a + 2));
	datastruct->our_environ[a] = cote_enas(name, value);
	datastruct->our_environ[a + 1] = NULL;
}

/**
 * set_env - Sets environment.
 * @datastruct: Relevant data.
 *
 * Return: 1 on success.
 */
int set_env(shell_info *datastruct)
{
	if (datastruct->args[1] == NULL || datastruct->args[2] == NULL)
	{
		find_error(datastruct, -1);
		return (1);
	}
	set_environ(datastruct->args[1], datastruct->args[2], datastruct);
	return (1);
}

/**
 * del_set_environ - Deletes an environment variable.
 * @datastruct: Data relevant.
 *
 * Return: 1 on success.
 */
int del_set_environ(shell_info *datastruct)
{
	char **realloc_environ;
	char *env_var, *env_name;
	int i, j, k;

	if (datastruct->args[1] == NULL)
	{
		find_err(datastruct, -1);
		return (1);
	}
	k = -1;
	for (i = 0; datastruct->our_environ[i]; i++)
	{
		env_var = str_dup(datastruct->our_environ[i]);
		env_name = str_tok(env_var, "=");
		if (str_comp(env_name, datastruct->args[1]) == 0)
		{
			k = i;
		}
		free(env_var);
	}
	if (k == -1)
	{
		find_err(datastruct, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (i));
	for (i = j = 0; datastruct->our_environ[i]; i++)
	{
		if (i != k)
		{
			realloc_environ[j] = datastruct->our_environ[i];
			j++;
		}
	}
	realloc_environ[j] = NULL;
	free(datastruct->our_environ[k]);
	free(datastruct->our_environ);
	datastruct->our_environ = realloc_environ;
	return (1);
}
