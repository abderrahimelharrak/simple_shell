#include "shell.h"

/**
 * **strtow_ - splits a string into words. Repeat delimiters are ignored
 * @s: the input string
 * @dl: the delimeter string
 * Return: success
 */

char **strtow_(char *s, char *dl)
{
	int x, y, z, m, num_words = 0;
	char **str;

	if (s == NULL || s[0] == 0)
		return (NULL);
	if (!dl)
		dl = " ";
	for (x = 0; s[x] != '\0'; x++)
		if (!_isdelim(s[x], dl) && (_isdelim(s[x + 1], dl) || !s[x + 1]))
			num_words++;

	if (num_words == 0)
		return (NULL);
	str = malloc((1 + num_words) * sizeof(char *));
	if (!str)
		return (NULL);
	for (x = 0, y = 0; y < num_words; y++)
	{
		while (_isdelim(s[x], dl))
			x++;
		z = 0;
		while (!_isdelim(s[x + z], dl) && s[x + z])
			z++;
		str[y] = malloc((z + 1) * sizeof(char));
		if (!str[y])
		{
			for (z = 0; z < y; z++)
				free(str[z]);
			free(str);
			return (NULL);
		}
		for (m = 0; m < z; m++)
			str[y][m] = s[x++];
		str[y][m] = 0;
	}
	str[y] = NULL;
	return (str);
}

/**
 * **strtow2_ - splits a string into words
 * @s: the input string
 * @dl: the delimeter
 * Return: a success
 */
char **strtow2_(char *s, char dl)
{
	int x, y, z, m, num_words = 0;
	char **str;

	if (s == NULL || s[0] == 0)
		return (NULL);
	for (x = 0; s[x] != '\0'; x++)
		if ((s[x] != dl && s[x + 1] == dl) ||
				    (s[x] != dl && !s[x + 1]) || s[x + 1] == dl)
			num_words++;
	if (num_words == 0)
		return (NULL);
	str = malloc((1 + num_words) * sizeof(char *));
	if (!str)
		return (NULL);
	for (x = 0, y = 0; y < num_words; y++)
	{
		while (s[x] == dl && s[x] != dl)
			x++;
		z = 0;
		while (s[x + z] != dl && s[x + z] && s[x + z] != dl)
			z++;
		str[y] = malloc((z + 1) * sizeof(char));
		if (!str[y])
		{
			for (z = 0; z < y; z++)
				free(str[z]);
			free(str);
			return (NULL);
		}
		for (m = 0; m < z; m++)
			str[y][m] = s[x++];
		str[y][m] = 0;
	}
	str[y] = NULL;
	return (str);
}

