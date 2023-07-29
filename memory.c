#include "main.h"

/**
 * mem_copy - Copies data between void pointers.
 * @destptr: Destination pointer.
 * @ptr: Source pointer.
 * @size: Size of pointer.
 *
 * Return: Nothing.
 */

void mem_copy(void *destptr, const void *ptr, unsigned int size)
{
	char *char_ptr = (char *)ptr;
	char *char_destptr = (char *)destptr;
	unsigned int n;

	for (n = 0; n < size; n++)
		char_destptr[n] = char_ptr[n];
}

/**
 * mem_realloc - Reallocates a memory block.
 * @ptr: Pointr to memory already allocated.
 * @prev_size: Allocated size of ptr.
 * @new_size: New size of new memory block.
 *
 * Return: Ptr.
 */

void *mem_realloc(void *ptr, unsigned int prev_size, unsigned int new_size)
{
	void *newptr;

	if (ptr == NULL)
		return (malloc(new_size));
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (new_size == prev_size)
		return (ptr);
	newptr = malloc(new_size);
	if (newptr == NULL)
		return (NULL);
	if (new_size < prev_size)
		mem_copy(newptr, ptr, new_size);
	else
		mem_copy(newptr, ptr, prev_size);

	free(ptr);
	return (newptr);
}
/**
 * dpmem_realloc - Reallocates a memory of double pointer.
 * @ptr: Double pointer.
 * @new_size: New memory block size.
 * @prev_size: Allocated size of pointer.
 *
 * Return: ptr.
 */

char **dpmem_realloc(char **ptr, unsigned int new_size, unsigned int prev_size)
{
	char **newptr;
	unsigned int n;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_size));
	if (new_size == prev_size)
		return (ptr);

	newptr = malloc(sizeof(char *) * new_size);
	if (newptr == NULL)
		return (NULL);

	for (n = 0; n < prev_size; n++)
		newptr[n] = ptr[n];

	free(ptr);
	return (newptr);
}
