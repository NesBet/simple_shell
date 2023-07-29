#include "main.h"

/**
 * ctcd_err - Concatenates message from cd error.
 *
 * @datastruct: Directory for relevant data.
 * @mssg: Message to be printed.
 * @error: Error message.
 * @cnt_str: Counter lines.
 *
 * Return: The error message.
 */

char *ctcd_err(shell_info *datastruct, char *mssg, char *error, char *cnt_str)
{
	char *error_flag;

	str_copy(error, datastruct->av[0]);
	str_cat(error, ": ");
	str_cat(error, cnt_str);
	str_cat(error, ": ");
	str_cat(error, datastruct->args[0]);
	str_cat(error, mssg);
	if (datastruct->args[1][0] == '-')
	{
		error_flag = malloc(3);
		error_flag[0] = '-';
		error_flag[1] = datastruct->args[1][1];
		error_flag[2] = '\0';
		str_cat(error, error_flag);
		free(error_flag);
	}
	else
	{
		str_cat(error, datastruct->args[1]);
	}
	str_cat(error, "\n");
	str_cat(error, "\0");
	return (error);
}

/**
 * error_cd - Error message for cd command.
 *
 * @datastruct: Directory.
 *
 * Return: Error message.
 */

char *error_cd(shell_info *datastruct)
{
	int size, len_id;
	char *error, *cnt_str, *mssg;

	cnt_str = conv_str(datastruct->count);
	if (datastruct->args[1][0] == '-')
	{
		mssg = " That option isn't available ";
		len_id = 2;
	}
	else
	{
		mssg = " Can't cd there ";
		len_id = str_len(datastruct->args[1]);
	}

	size = str_len(datastruct->av[0] + str_len(datastruct->args[0]));
	size += str_len(cnt_str) + str_len(mssg) + len_id + 5;
	error = malloc(sizeof(char) * (size + 1));

	if (error == 0)
	{
		free(cnt_str);
		return (NULL);
	}

	error = ctcd_err(datastruct, mssg, error, cnt_str);
	free(cnt_str);
	return (error);
}

/**
 * not_found - Error message for command not found.
 * @datastruct: Directory.
 *
 * Return: Error message.
 */

char *not_found(shell_info *datastruct)
{
	int size;
	char *cnt_str;
	char *error;

	cnt_str = conv_str(datastruct->count);
	size = str_len(datastruct->av[0]) + str_len(cnt_str);
	size += str_len(datastruct->args[0] + 16);
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
	str_cat(error, " Not recognized\n");
	str_cat(error, "\0");
	free(cnt_str);
	return (error);
}

/**
 * shell_exit - Error message.
 *
 * @datastruct: Data.
 *
 * Return: An error message.
 */

char *shell_exit(shell_info * datastruct)
{
	int size;
	char *cnt_str;
	char *error;

	cnt_str = conv_str(datastruct->count);
	size = str_len(datastruct->av[0] + str_len(cnt_str));
	size += str_len(datastruct->args[0]) + str_len(datastruct->args[1]) + 23;
	error = malloc(sizeof(char) * (size + 1));
	if (error == 0)
	{
		free(cnt_str);
		return (NULL);
	}
	str_copy(error, datastruct->av[0]);
	str_cat(error, ": ");
	str_cat(error, cnt_str);
	str_cat(error, ": ");
	str_cat(error, datastruct->args[0]);
	str_cat(error, ": Number ain't allowed ");
	str_cat(error, datastruct->args[1]);
	str_cat(error, "\n\0");
	free(cnt_str);
	return (error);
}
