#include "shell.h"

/**
 * eputs_ - prints an input string
 * @ptr: the string to be printed
 * Return: success
 */
void eputs_(char *ptr)
{
	int x = 0;

	if (!ptr)
		return;
	while (ptr[x] != '\0')
	{
		eputchar_(ptr[x]);
		x++;
	}
}

/**
 * eputchar_ - writes the character c to stderr
 * @ctr: The character to print
 * Return: success
 */
int eputchar_(char ctr)
{
	static int x;
	static char buff[WRITE_BUFF_SIZE];

	if (ctr == BUFF_FLUSH || x >= WRITE_BUFF_SIZE)
	{
		write(2, buff, x);
		x = 0;
	}
	if (ctr != BUFF_FLUSH)
		buff[x++] = ctr;
	return (1);
}

/**
 * putfd_ - writes the character c to given fd
 * @ctr: The character to print
 * @f: The filedescriptor to write to
 * Return: success
 */
int putfd_(char ctr, int f)
{
	static int x;
	static char buff[WRITE_BUFF_SIZE];

	if (ctr == BUFF_FLUSH || x >= WRITE_BUFF_SIZE)
	{
		write(f, buff, x);
		x = 0;
	}
	if (ctr != BUFF_FLUSH)
		buff[x++] = ctr;
	return (1);
}

/**
 * putsfd_ - prints an input string
 * @ptr: the string to be printed
 * @f: the filedescriptor to write to
 * Return: success
 */
int putsfd_(char *ptr, int f)
{
	int x = 0;

	if (!ptr)
		return (0);
	while (*ptr)
	{
		x += putfd_(*ptr++, f);
	}
	return (x);
}

