#include "main.h"

/**
 * check_env - Checks for env variable.
 * @h: Head of linked list.
 * @in: Input string.
 * @data: Data structure.
 *
 * Return: Nothing.
 */
void check_env(rd_var **h, char *in, shell_info *data)
{
	int row, chr, j, lval;
	char **_envr;

	_envr = data->our_environ;
	for (row = 0; _envr[row]; row++)
	{
		for (j = 1, chr = 0; _envr[row][chr]; chr++)
		{
			if (_envr[row][chr] == '=')
			{
				lval = str_len(_envr[row] + chr + 1);
				add_node_rdvar(h, j, _envr[row] + chr + 1, lval);
				return;
			}

			if (in[j] == _envr[row][chr])
				j++;
			else
				break;
		}
	}

	for (j = 0; in[j]; j++)
	{
		if (in[j] == ' ' || in[j] == '\t' || in[j] == ';' || in[j] == '\n')
			break;
	}

	add_node_rdvar(h, j, NULL, 0);
}

/**
 * check_vars - Checks if the typed variable is $$ or $?.
 * @h: Head of the linked list.
 * @in: Input string.
 * @st: Last status of Shell.
 * @data: Data structure.
 *
 * Return: Nothing.
 */
int check_vars(rd_var **h, char *in, char *st, shell_info *data)
{
	int i, lst, lpd;

	lst = str_len(st);
	lpd = str_len(data->pid);

	for (i = 0; in[i]; i++)
	{
		if (in[i] == '$')
		{
			if (in[i + 1] == '?')
				add_node_rdvar(h, 2, st, lst), i++;
			else if (in[i + 1] == '$')
				add_node_rdvar(h, 2, data->pid, lpd), i++;
			else if (in[i + 1] == '\n')
				add_node_rdvar(h, 0, NULL, 0);
			else if (in[i + 1] == '\0')
				add_node_rdvar(h, 0, NULL, 0);
			else if (in[i + 1] == ' ')
				add_node_rdvar(h, 0, NULL, 0);
			else if (in[i + 1] == '\t')
				add_node_rdvar(h, 0, NULL, 0);
			else if (in[i + 1] == ';')
				add_node_rdvar(h, 0, NULL, 0);
			else
				check_env(h, in + i, data);
		}
	}

	return (i);
}

/**
 * repl_vars - Replaces string into variables.
 *
 * @head: Head of the linked list.
 * @input: Input string.
 * @new_input: New input string.
 * @new_len: new length
 *
 * Return: String.
 */
char *repl_vars(rd_var **head, char *input, char *new_input, int new_len)
{
	rd_var *indx;
	int i, j, k;

	indx = *head;
	for (j = i = 0; i < new_len; i++)
	{
		if (input[j] == '$')
		{
			if (!(indx->len_var) && !(indx->len_val))
			{
				new_input[i] = input[j];
				j++;
			}
			else if (indx->len_var && !(indx->len_val))
			{
				for (k = 0; k < indx->len_var; k++)
					j++;
				i--;
			}
			else
			{
				for (k = 0; k < indx->len_val; k++)
				{
					new_input[i] = indx->val[k];
					i++;
				}
				j += (indx->len_var);
				i--;
			}
			indx = indx->next;
		}
		else
		{
			new_input[i] = input[j];
			j++;
		}
	}

	return (new_input);
}

/**
 * rep_var - Calls.
 *
 * @input: Input string.
 * @datastruct: Data structure.
 *
 * Return: String.
 */

char *rep_var(char *input, shell_info *datastruct)
{
	rd_var *head, *indx;
	char *status, *new_input;
	int old_len, new_len;

	status = conv_str(datastruct->status);
	head = NULL;

	old_len = check_vars(&head, input, status, datastruct);
	if (head == NULL)
	{
		free(status);
		return (input);
	}

	indx = head;
	new_len = 0;

	while (indx != NULL)
	{
		new_len += (indx->len_val - indx->len_var);
		indx = indx->next;
	}

	new_len += old_len;

	new_input = malloc(sizeof(char) * (new_len + 1));
	new_input[new_len] = '\0';

	new_input = repl_vars(&head, input, new_input, new_len);

	free(input);
	free(status);
	free_rdvar_list(&head);

	return (new_input);
}
