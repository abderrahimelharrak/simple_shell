#include "shell.h"

/**
 * memset_ - fills memory with a constant byte
 * @str: the pointer to the memory area
 * @btr: the byte to fill *s with
 * @num: the amount of bytes to be filled
 * Return: success
 */
char *memset_(char *str, char btr, unsigned int num)
{
	unsigned int x;

	for (x = 0; x < num; x++)
		str[x] = btr;
	return (str);
}

/**
 * ffree_ - frees a string of strings
 * @p: string of strings
 * Return: success
 */
void ffree_(char **p)
{
	char **all = p;

	if (!p)
		return;
	while (*p)
		free(*p++);
	free(all);
}

/**
 * realloc_ - reallocates a block of memory
 * @p: pointer to previous malloc'ated block
 * @old_s: byte size of previous block
 * @new_s: byte size of new block
 * Return: success
 */
void *realloc_(void *p, unsigned int old_s, unsigned int new_s)
{
	char *ptr;

	if (!p)
		return (malloc(new_s));
	if (!new_s)
		return (free(p), NULL);
	if (new_s == old_s)
		return (p);

	ptr = malloc(new_s);
	if (!ptr)
		return (NULL);

	old_s = old_s < new_s ? old_s : new_s;
	while (old_s--)
		ptr[old_s] = ((char *)p)[old_s];
	free(p);
	return (p);
}
