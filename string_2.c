#include "shell.h"

/**
 * strcpy_ - copies a string
 * @dest: the destination
 * @src: the source
 * Return: success
 */
char *strcpy_(char *dest, char *src)
{
	int x = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[x])
	{
		dest[x] = src[x];
		x++;
	}
	dest[x] = 0;
	return (dest);
}

/**
 * strdup_ - duplicates a string
 * @s: the string to duplicate
 * Return: success
 */
char *strdup_(const char *s)
{
	int leng = 0;
	char *r;

	if (s == NULL)
		return (NULL);
	while (*s++)
		leng++;
	r = malloc(sizeof(char) * (leng + 1));
	if (!r)
		return (NULL);
	for (leng++; leng--;)
		r[leng] = *--s;
	return (r);
}

/**
 * puts_ - prints an input string
 * @s: the string to be printed
 * Return: success
 */
void puts_(char *s)
{
	int x = 0;

	if (!s)
		return;
	while (s[x] != '\0')
	{
		putchar_(s[x]);
		x++;
	}
}

/**
 * putchar_ - writes the character c to stdout
 * @ctr: The character to print
 * Return: success
 */
int putchar_(char ctr)
{
	static int x;
	static char buff[WRITE_BUFF_SIZE];

	if (ctr == BUFF_FLUSH || x >= WRITE_BUFF_SIZE)
	{
		write(1, buff, x);
		x = 0;
	}
	if (ctr != BUFF_FLUSH)
		buff[x++] = ctr;
	return (1);
}
