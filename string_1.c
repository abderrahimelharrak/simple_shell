#include "shell.h"

/**
 * strlen_ - returns the length of a string
 * @str: the string whose length to check
 * Return: success
 */
int strlen_(char *str)
{
	int x = 0;

	if (!str)
		return (0);

	while (*str++)
		x++;
	return (x);
}

/**
 * strcmp_ - performs lexicogarphic comparison of two strangs.
 * @str1: the first strang
 * @str2: the second strang
 * Return: success
 */
int strcmp_(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * _startswith - checks if needle starts with haystack
 * @hstack: string to search
 * @nedle: the substring to find
 * Return: success
 */
char *_startswith(const char *hstack, const char *nedle)
{
	while (*nedle)
		if (*nedle++ != *hstack++)
			return (NULL);
	return ((char *)hstack);
}

/**
 * strcat_ - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 * Return: success
 */
char *strcat_(char *dest, char *src)
{
	char *r = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (r);
}

