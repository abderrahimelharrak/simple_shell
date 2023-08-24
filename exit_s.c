
#include "shell.h"

/**
 * strncpy_ - copies a string
 *@dest: the destination string to be copied to
 *@src: the source string
 *@num: the amount of characters to be copied
 *Return: success
 */
char *strncpy_(char *dest, char *src, int num)
{
	int x, y;
	char *str = dest;

	x = 0;
	while (src[x] != '\0' && x < num - 1)
	{
		dest[x] = src[x];
		x++;
	}
	if (x < num)
	{
		y = x;
		while (y < num)
		{
			dest[y] = '\0';
			y++;
		}
	}
	return (str);
}

/**
 * strncat_ - concatenates two strings
 *@dest: the first string
 *@src: the second string
 *@num: the amount of bytes to be maximally used
 *Return: success
 */
char *strncat_(char *dest, char *src, int num)
{
	int x, y;
	char *str = dest;

	x = 0;
	y = 0;
	while (dest[x] != '\0')
		x++;
	while (src[y] != '\0' && y < num)
	{
		dest[x] = src[y];
		x++;
		y++;
	}
	if (y < num)
		dest[x] = '\0';
	return (str);
}

/**
 * strchr_ - locates a character in a string
 *@str: the string to be parsed
 *@ctr: the character to look for
 *Return: success
 */
char *strchr_(char *str, char ctr)
{
	do {
		if (*str == ctr)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}
