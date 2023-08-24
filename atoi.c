#include "shell.h"

/**
 * inter_active - returns true if shell is interactive mode
 * @info: struct address
 * Return: 1 if interactive mode, 0 otherwise
 */
int inter_active(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfiled <= 2);
}

/**
 * _isdelim - checks if character is a delimeter
 * @c: the char to check
 * @delim: the delimeter string
 * Return: success
 */
int _isdelim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * is_alpha - checks for alphabetic character
 * @c: The character to input
 * Return: success
 */

int is_alpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * atoi_ - converts a string to an integer
 * @s: the string to be converted
 * Return: success
 */

int atoi_(char *s)
{
	int i, signe = 1, flage = 0, out_put;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flage != 2; i++)
	{
		if (s[i] == '-')
			signe *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flage = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flage == 1)
			flage = 2;
	}

	if (signe == -1)
		out_put = -result;
	else
		out_put = result;

	return (out_put);
}

