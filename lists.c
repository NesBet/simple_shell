#include "main.h"

/**
 * end_separator - Adds a separator at the end.
 * @head: Head of linked list.
 * @separator: Separator used.
 *
 * Return: Address of head.
 */

list_separator *end_separator(list_separator **head, char separator)
{
	list_separator *new, *tempo;

	new = malloc(sizeof(list_separator));
	if (new == NULL)
		return (NULL);

	new->separator = separator;
	new->next = NULL;
	tempo = *head;
	if (tempo == NULL)
	{
		*head = new;
	}
	else
	{
		while (tempo->next != NULL)
			tempo = tempo->next;
		tempo->next = new;
	}
	return (*head);
}

/**
 * free_list_separator - Frees a list separato.
 * @head: Head of linked list.
 *
 * Return: Nothing.
 */
void free_list_separator(list_separator **head)
{
	list_separator *tempo;
	list_separator *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((tempo = curr) != NULL)
		{
			curr = curr->next;
			free(tempo);
		}
		*head = NULL;
	}
}

/**
 * end_line_node - Adds a command line at end of  line list.
 * @head: Head of linked list.
 * @line: The command line.
 *
 * Return: Head's address.
 */

line_list *end_line_node(line_list **head, char *line)
{
	line_list *new, *tempo;

	new = malloc(sizeof(line_list));
	if (new == NULL)
		return (NULL);
	new->line = line;
	new->next = NULL;
	tempo = *head;

	if (tempo == NULL)
	{
		*head = new;
	}
	else
	{
		while (tempo->next != NULL)
			tempo = tempo->next;
		tempo->next = new;
	}

	return (*head);
}

/**
 * free_line_list - Frees a line list.
 * @head: Head of linked list.
 *
 * Return: Nothing.
 */

void free_line_list(line_list **head)
{
	line_list *tempo;
	line_list *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((tempo = curr) != NULL)
		{
			curr = curr->next;
			free(tempo);
		}
		*head = NULL;
	}
}
