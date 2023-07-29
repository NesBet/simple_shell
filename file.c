#include "main.h"

/**
 * environ_err - Environment error message.
 * @datastruct: Relevant data that is required.
 *
 * Return: The error message.
 */

char *environ_err(shell_info *datastruct)
{
	int size;
	char *error;
	char *cnt_str;
	char *mssg;


	cnt_str = conv_str(datastruct->count);
	mssg = "Unable to modify environment\n";
	size = str_len(datastruct->av[0]) + str_len(cnt_str);
	size += str_len(datastruct->args[0]) + str_len(mssg) + 4;
	error = malloc(sizeof(char) * (size + 1));
	if (error == 0)
	{
		free(error);
		free(cnt_str);
		return (NULL);
	}

	str_copy(error, datastruct->av[0]);
	str_cat(error, ": ");
	str_cat(error, cnt_str);
	str_cat(error, ": ");
	str_cat(error, datastruct->args[0]);
	str_cat(error, mssg);
	str_cat(error, "\0");
	free(cnt_str);
	return (error);
}

/**
 * error_path - Path message failure.
 * @datastruct: Relvant data.
 *
 * Return: The error message.
 */

char *error_path(shell_info *datastruct)
{
	int size;
	char *error;
	char *cnt_str;

	cnt_str = conv_str(datastruct->count);
	size = str_len(datastruct->av[0]) + str_len(cnt_str);
	size += str_len(datastruct->args[0]) + 24;
	error = malloc(sizeof(char) * (size + 1));
	if (error == 0)
	{
		free(error);
		free(cnt_str);
		return (NULL);
	}
	str_copy(error, datastruct->av[0]);
	str_cat(error, ": ");
	str_cat(error, cnt_str);
	str_cat(error, ": ");
	str_cat(error, datastruct->args[0]);
	str_cat(error, ": You do not have necessary permission\n");
	str_cat(error, "\0");
	free(cnt_str);
	return (error);
}
