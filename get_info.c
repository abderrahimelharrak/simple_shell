#include "shell.h"

/**
 * _clearinfo - initializes info_t struct
 * @info: struct address
 * Return: success
 */
void _clearinfo(info_t *info)
{
	info->argum = NULL;
	info->argumv = NULL;
	info->pathe = NULL;
	info->argumc = 0;
}

/**
 * _setinfo - initializes info_t struct
 * @info: struct address
 * @argv: argument vector
 * Return: success
 */
void _setinfo(info_t *info, char **argv)
{
	int x = 0;

	info->filename = argv[0];
	if (info->argum)
	{
		info->argumv = strtow_(info->argum, " \t");
		if (!info->argumv)
		{
			info->argumv = malloc(sizeof(char *) * 2);
			if (info->argumv)
			{
				info->argumv[0] = strdup_(info->argum);
				info->argumv[1] = NULL;
			}
		}
		for (x = 0; info->argumv && info->argumv[x]; x++)
			;
		info->argumc = x;

		_replacealias(info);
		_replacevars(info);
	}
}

/**
 * _freeinfo - frees info_t struct fields
 * @info: struct address
 * @a: true if freeing all fields
 * Return: success
 */
void _freeinfo(info_t *info, int a)
{
	ffree_(info->argumv);
	info->argumv = NULL;
	info->pathe = NULL;
	if (a)
	{
		if (!info->cmd_buff)
			free(info->argum);
		if (info->envv)
			_freelist(&(info->envv));
		if (info->historique)
			_freelist(&(info->historique));
		if (info->aliass)
			_freelist(&(info->aliass));
		ffree_(info->environn);
			info->environn = NULL;
		bfree_((void **)info->cmd_buff);
		if (info->readfiled > 2)
			close(info->readfiled);
		putchar_(BUFF_FLUSH);
	}
}
