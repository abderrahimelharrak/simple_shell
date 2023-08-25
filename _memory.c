#include "shell.h"

/**
 * bfree_ - frees a pointer and NULLs the address
 * @p: address of the pointer to free
 * Return: success
 */
int bfree_(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}

