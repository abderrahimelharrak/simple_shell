#include "shell.h"

/**
 * _getenviron - returns the string array copy of our environ
 * @info: Struct
 * Return: success
 */
char **_getenviron(info_t *info)
{
	if (!info->environn || info->env_change)
	{
		info->environn = _listto_strings(info->envv);
		info->env_change = 0;
	}

	return (info->environn);
}

/**
 * unsetenv_ - Remove an environment variable
 * @info: Struct
 *  Return: success
 * @v: the string env var property
 */
int unsetenv_(info_t *info, char *v)
{
	list_t *nod = info->envv;
	size_t x = 0;
	char *ptr;

	if (!nod || !v)
		return (0);

	while (nod)
	{
		ptr = _startswith(nod->string, v);
		if (ptr && *ptr == '=')
		{
			info->env_change = _deletenode_at_index(&(info->envv), x);
			x = 0;
			nod = info->envv;
			continue;
		}
		nod = nod->next;
		x++;
	}
	return (info->env_change);
}

/**
 * setenv_ - Initialize a new environment var
 * @info: Struct
 * @v: the string env var property
 * @val: the string env var value
 *  Return: success
 */
int setenv_(info_t *info, char *v, char *val)
{
	char *buff = NULL;
	list_t *nod;
	char *ptr;

	if (!v || !val)
		return (0);

	buff = malloc(strlen_(v) + strlen_(val) + 2);
	if (!buff)
		return (1);
	strcpy_(buff, v);
	strcat_(buff, "=");
	strcat_(buff, val);
	nod = info->envv;
	while (nod)
	{
		ptr = _startswith(nod->string, v);
		if (ptr && *ptr == '=')
		{
			free(nod->string);
			nod->string = buff;
			info->env_change = 1;
			return (0);
		}
		nod = nod->next;
	}
	_addnode_end(&(info->envv), buff, 0);
	free(buff);
	info->env_change = 1;
	return (0);
}

