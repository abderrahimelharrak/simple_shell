#include "shell.h"

/**
 * _iscmd - determines if a file is an executable command
 * @info: the info struct
 * @pathe: path to the file
 * Return: success
 */
int _iscmd(info_t *info, char *pathe)
{
	struct stat st;

	(void)info;
	if (!pathe || stat(pathe, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * _dupchars - duplicates characters
 * @path_str: the PATH string
 * @strt: starting index
 * @stp: stopping index
 * Return: success
 */
char *_dupchars(char *path_str, int strt, int stp)
{
	static char buff[1024];
	int x = 0, z = 0;

	for (z = 0, x = strt; x < stp; x++)
		if (path_str[x] != ':')
			buff[z++] = path_str[x];
	buff[z] = 0;
	return (buff);
}

/**
 * _findpath - finds this cmd in the PATH string
 * @info: the info struct
 * @path_str: the PATH string
 * @comd: the cmd to find
 * Return: success
 */
char *_findpath(info_t *info, char *path_str, char *comd)
{
	int x = 0, currpos = 0;
	char *pathe;

	if (!path_str)
		return (NULL);
	if ((strlen_(comd) > 2) && _startswith(comd, "./"))
	{
		if (_iscmd(info, comd))
			return (comd);
	}
	while (1)
	{
		if (!path_str[x] || path_str[x] == ':')
		{
			pathe = _dupchars(path_str, currpos, x);
			if (!*pathe)
				strcat_(pathe, comd);
			else
			{
				strcat_(pathe, "/");
				strcat_(pathe, comd);
			}
			if (_iscmd(info, pathe))
				return (pathe);
			if (!path_str[x])
				break;
			currpos = x;
		}
		x++;
	}
	return (NULL);
}

