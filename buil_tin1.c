#include "shell.h"

/**
 * myhistory_ - displays the history list
 * @info: Struct
 *  Return: success
 */
int myhistory_(info_t *info)
{
	_printlist(info->historique);
	return (0);
}

/**
 * _unsetalias - sets alias to string
 * @info: parameter struct
 * @s: the string alias
 * Return: success
 */
int _unsetalias(info_t *info, char *s)
{
	char *ptr, ctr;
	int ret;

	ptr = strchr_(s, '=');
	if (!ptr)
		return (1);
	ctr = *ptr;
	*ptr = 0;
	ret = _deletenode_at_index(&(info->aliass),
		_getnode_index(info->aliass, _nodestarts_with(info->aliass, s, -1)));
	*ptr = ctr;
	return (ret);
}

/**
 * _setalias - sets alias to string
 * @info: parameter struct
 * @s: the string alias
 * Return: success
 */
int _setalias(info_t *info, char *s)
{
	char *ptr;

	ptr = strchr_(s, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (_unsetalias(info, s));

	_unsetalias(info, s);
	return (_addnode_end(&(info->aliass), s, 0) == NULL);
}

/**
 * _printalias - prints an alias string
 * @nod: the alias
 * Return: success
 */
int _printalias(list_t *nod)
{
	char *ptr = NULL, *atr = NULL;

	if (nod)
	{
		ptr = strchr_(nod->string, '=');
		for (atr = nod->string; atr <= ptr; atr++)
		putchar_(*atr);
		putchar_('\'');
		puts_(ptr + 1);
		puts_("'\n");
		return (0);
	}
	return (1);
}

/**
 * myalias_ - mimics the alias builtin (man alias)
 * @info: Struct
 *  Return: success
 */
int myalias_(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *nod = NULL;

	if (info->argumc == 1)
	{
		nod = info->aliass;
		while (nod)
		{
			_printalias(nod);
			nod = nod->next;
		}
		return (0);
	}
	for (i = 1; info->argumv[i]; i++)
	{
		p = strchr_(info->argumv[i], '=');
		if (p)
			_setalias(info, info->argumv[i]);
		else
			_printalias(_nodestarts_with(info->aliass, info->argumv[i], '='));
	}

	return (0);
}

