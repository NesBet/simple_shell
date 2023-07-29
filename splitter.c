#include "main.h"

/**
 * swap_char - Swaps.
 * @input: input string
 * @bool: Swap type.
 *
 * Return: Swapped string.
 */
char *swap_char(char *input, int bool)
{
	int i;

	if (bool == 0)
	{
		for (i = 0; input[i]; i++)
		{
			if (input[i] == '|')
			{
				if (input[i + 1] != '|')
					input[i] = 16;
				else
					i++;
			}

			if (input[i] == '&')
			{
				if (input[i + 1] != '&')
					input[i] = 12;
				else
					i++;
			}
		}
	}
	else
	{
		for (i = 0; input[i]; i++)
		{
			input[i] = (input[i] == 16 ? '|' : input[i]);
			input[i] = (input[i] == 12 ? '&' : input[i]);
		}
	}
	return (input);
}

/**
 * add_nodes - Adds.
 * @head_sep: Head of separator list.
 * @head_list: Head of list.
 * @input: Input string.
 *
 * Return: Nothing.
 */

void add_nodes(list_separator **head_sep, line_list **head_list, char *input)
{
	int i;
	char *line;

	input = swap_char(input, 0);

	for (i = 0; input[i]; i++)
	{
		if (input[i] == ';')
			end_separator(head_sep, input[i]);

		if (input[i] == '|' || input[i] == '&')
		{
			end_separator(head_sep, input[i]);
			i++;
		}
	}

	line = str_tok(input, ";|&");
	do {
		line = swap_char(line, 1);
		end_separator(head_list, line);
		line = str_tok(NULL, ";|&");
	} while (line != NULL);
}

/**
 * go_next - Move to next command line stored.
 *
 * @list_sep: Separator list
 * @list_li: Command line list.
 * @datastruct: Data structure.
 *
 * Return: Nothing.
 */
void go_next(list_separator **list_sep, line_list **list_li, shell_info *datastruct)
{
	int loop_sep;
	sep_list *ls_s;
	line_list *ls_l;

	loop_sep = 1;
	ls_s = *list_sep;
	ls_l = *list_li;

	while (ls_s != NULL && loop_sep)
	{
		if (datastruct->status == 0)
		{
			if (ls_s->separator == '&' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->separator == '|' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !loop_sep)
			ls_s = ls_s->next;
	}

	*ls_s = ls_s;
	*list_li = ls_l;
}

/**
 * split_commands - Splits command lines.
 *
 * @datastruct: Data structure.
 * @input: Input string.
 *
 * Return: 0 to exit.
 */
int split_commands(shell_info *datastruct, char *input)
{

	list_separator *head_s, *list_separator;
	line_list *head_l, *list_l;
	int loop;

	head_s = NULL;
	head_l = NULL;

	add_nodes(&head_s, &head_l, input);

	list_s = head_s;
	list_l = head_l;

	while (list_l != NULL)
	{
		datastruct->command = list_l->line;
		datastruct->args = split_line(datastruct->command);
		loop = line_executor(datastruct);
		free(datastruct->args);

		if (loop == 0)
			break;

		go_next(&list_s, &list_l, datastruct);

		if (list_l != NULL)
			list_l = list_l->next;
	}

	free_line_list(&head_s);
	free_line_list(&head_l);

	if (loop == 0)
		return (0);
	return (1);
}

/**
 * split_line - Tokenizes the input string.
 * @input: input string.
 *
 * Return: string splitted.
 */
char **split_line(char *input)
{
	size_t bsize;
	size_t i;
	char **tokens;
	char *token;

	bsize = TOK_BUFSIZE;
	tokens = malloc(sizeof(char *) * (bsize));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": Allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = str_tok(input, TOK_DELIM);
	tokens[0] = token;

	for (i = 1; token != NULL; i++)
	{
		if (i == bsize)
		{
			bsize += TOK_BUFSIZE;
			tokens = dpmem_realloc(tokens, i, sizeof(char *) * bsize);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": Allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = str_tok(NULL, TOK_DELIM);
		tokens[i] = token;
	}
	return (tokens);
}
