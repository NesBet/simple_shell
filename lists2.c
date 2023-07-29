#include "main.h"

/**
 * add_node_rdvar - Adds a variable at end of rd_var.
 * @head: Head of linked list.
 * @valvar: Value of variable.
 * @lenval: Length of value.
 * @lenvar: Length of variable.
 *
 * Return: Head's address.
 */

rd_var *add_node_rdvar(rd_var **head, int lenvar, char *valvar, int lenval)
{
	rd_var *new, *tempo;

	new = malloc(sizeof(rd_var));
	if (new == NULL)
		return (NULL);

	new->len_val = lenval;
	new->valvar = valvar;
	new->len_var = lenvar;

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
 * free_rdvar_list - Frees a rd_var list.
 * @head: Head of linked list.
 *
 * Return: Nothing.
 */
void free_rdvar_list(rd_var **head)
{
	rd_var *curr;
	rd_var *tempo;

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
