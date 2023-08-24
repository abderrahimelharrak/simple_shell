#include "shell.h"

/**
 * myenv_ - prints the current environment
 * @info: Struct
 * Return: success
 */
int myenv_(info_t *info)
{
	_printlist_str(info->envv);
	return (0);
}

/**
 * getenv_ - gets the value of an environ variable
 * @info: Struct
 * @n: env var name
 * Return: success
 */
char *getenv_(info_t *info, const char *n)
{
	list_t *nod = info->envv;
	char *ptr;

	while (nod)
	{
		ptr = _startswith(nod->string, n);
		if (ptr && *ptr)
			return (ptr);
		nod = nod->next;
	}
	return (NULL);
}

/**
 * mysetenv_ - Initialize a new env
 * @info: Struct
 *  Return: success
 */
int mysetenv_(info_t *info)
{
	if (info->argumc != 3)
	{
		eputs_("Incorrect number of arguements\n");
		return (1);
	}
	if (setenv_(info, info->argumv[1], info->argumv[2]))
		return (0);
	return (1);
}

/**
 * myunsetenv_ - Remove an environment variable
 * @info: Struct
 * Return: success
 */
int myunsetenv_(info_t *info)
{
	int x;

	if (info->argumc == 1)
	{
		eputs_("Too few arguements.\n");
		return (1);
	}
	for (x = 1; x <= info->argumc; x++)
		unsetenv_(info, info->argumv[x]);

	return (0);
}

/**
 * _populateenv_list - populates env linked list
 * @info: Struct
 * Return: success
 */
int _populateenv_list(info_t *info)
{
	list_t *nod = NULL;
	size_t x;

	for (x = 0; environement[x]; x++)
		_addnode_end(&nod, environement[x], 0);
	info->envv = nod;
	return (0);
}

