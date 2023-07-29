#include "main.h"

/**
 * curr_dir - Checks whether in the current directory.
 * @path: Char pointer.
 * @n: Pointer to index location.
 *
 * Return: 1 if found in cd, 0 otherwise.
 */

int curr_dir(char *path, int *n)
{
	if (path[*n] == ':')
		return (1);

	while (path[*n] != ':' && path[*n])
	{
		*n += 1;
	}

	if (path[*n])
		*n += 1;

	return (0);
}
/**
 * locate_cmd - Finds a command.
 * @cmd: Name of command.
 * @our_environ: Variable for the environment.
 *
 * Return: Where command is located.
 */

char *locate_cmd(char *cmd, char **our_environ)
{
	char *route, *ptr_route, *token_path, *dir;
	int len_dir, len_cmd, n;
	struct stat st;

	route = get_env("PATH", our_environ);
	if (route)
	{
		ptr_route = str_dup(route);
		len_cmd = str_len(cmd);
		token_path = str_tok(ptr_route, ":");
		n = 0;
		while (token_path != NULL)
		{
			if (curr_dir(route, &n))
				if (stat(cmd, &st) == 0)
					return (cmd);
			len_dir = str_len(token_path);
			dir = malloc(len_dir + len_cmd + 2);
			str_copy(dir, token_path);
			str_cat(dir, "/");
			str_cat(dir, cmd);
			str_cat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(ptr_route);
				return (dir);
			}
			free(dir);
			token_path = str_tok(NULL, ":");
		}
		free(ptr_route);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}

/**
 * check_executable - Checks whether a command is executable.
 * @datastruct: Data structure used.
 *
 * Return: Only 0 if it ain't executable.
 */

int check_executable(shell_info *datastruct)
{
	struct stat st;
	int n;
	char *command;

	command = datastruct->args[0];

	for (n = 0; command[n]; n++)
	{
		if (command[n] == '.')
		{
			if (command[n + 1] == '.')
				return (0);
			if (command[n + 1] == '/')
				continue;
			else
				break;
		}
		else if (command[n] == '/' && n != 0)
		{
			if (command[n + 1] == '.')
				continue;
			n++;
			break;
		}
		else
			break;

	}

	if (n == 0)
		return (0);
	if (stat(command + n, &st) == 0)
	{
		return (n);
	}
	find_error(datastruct, 127);
	return (-1);
}

/**
 * error_command - Handles user permission requests.
 * @dir: Final directory.
 * @datastruct: The data structure.
 *
 * Return: 0 for success and 1 for error(s).
 */

int error_command(char *dir, shell_info *datastruct)
{
	if (dir == NULL)
	{
		find_error(datastruct, 127);
		return (1);
	}

	if (str_comp(datastruct->args[0], dir) != 0)
	{
		if (access(dir, F_OK) == -1)
		{
			find_error(datastruct, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(datastruct->args[0], F_OK) == -1)
		{
			find_error(datastruct, 126);
			return (1);
		}
	}
	return (0);
}

/**
 * command_line - Executes command line arguments.
 * @datastruct: Arguments and necessary inputs.
 *
 * Return: 1 for success, otherwise for error.
 */

int command_line(shell_info *datastruct)
{
	(void) wrpd;
	char *dir;
	pid_t wtpd;
	pid_t pd;
	int condition;
	int run;

	run = check_executable(datastruct);
	if (run == -1)
		return (1);
	if (run == 0)
	{
		dir = locate_cmd(datastruct->[0], datastruct->our_environ);
		if (error_command(dir, datastruct) == 1)
			return (1);
	}
	pd = fork();
	if (pd == 0)
	{
		if (run == 0)
			dir = locate_cmd(datastruct->args[0], datastruct->our_environ);
		else
			dir = datastruct->args[0];
		execve(dir + run, datastruct->args, datastruct->our_environ);
	}
	else if (pd < 0)
	{
		perror(datastruct->av[0]);
		return (1);
	}
	else
	{
		do {
			wtpd = waitpid(pd, &condition, WUNTRACED);

		} while (!WIFEXITED(condition) && !WIFSIGNALED(condition));
	}
	datastruct->status = condition / 256;
	return (1);
}
