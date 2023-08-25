#include "shell.h"

/**
 * _listlen - determines length of linked list
 * @hd: pointer to first node
 * Return: success
 */
size_t _listlen(const list_t *hd)
{
	size_t x = 0;

	while (hd)
	{
		hd = hd->next;
		x++;
	}
	return (x);
}

/**
 * _listto_strings - returns an array of strings of the list->str
 * @hd: pointer to first node
 * Return: success
 */
char **_listto_strings(list_t *hd)
{
	list_t *nod = hd;
	size_t x = _listlen(hd), y;
	char **strs;
	char *str;

	if (!hd || !x)
		return (NULL);
	strs = malloc(sizeof(char *) * (x + 1));
	if (!strs)
		return (NULL);
	for (x = 0; nod; nod = nod->next, x++)
	{
		str = malloc(strlen_(nod->string) + 1);
		if (!str)
		{
			for (y = 0; y < x; y++)
				free(strs[y]);
			free(strs);
			return (NULL);
		}

		str = strcpy_(str, nod->string);
		strs[x] = str;
	}
	strs[x] = NULL;
	return (strs);
}


/**
 * _printlist - prints all elements of a list_t linked list
 * @hd: pointer to first node
 * Return: success
 */
size_t _printlist(const list_t *hd)
{
	size_t x = 0;

	while (hd)
	{
		puts_(_convertnumber(hd->num, 10, 0));
		putchar_(':');
		putchar_(' ');
		puts_(hd->string ? hd->string : "(nil)");
		puts_("\n");
		hd = hd->next;
		x++;
	}
	return (x);
}

/**
 * _nodestarts_with - returns node whose string starts with prefix
 * @nod: pointer to list head
 * @pre_fix: string to match
 * @ctr: the next character after prefix to match
 * Return: success
 */
list_t *_nodestarts_with(list_t *nod, char *pre_fix, char ctr)
{
	char *ptr = NULL;

	while (nod)
	{
		ptr = _startswith(nod->string, pre_fix);
		if (ptr && ((ctr == -1) || (*ptr == ctr)))
			return (nod);
		nod = nod->next;
	}
	return (NULL);
}

/**
 * _getnode_index - gets the index of a node
 * @hd: pointer to list head
 * @nod: pointer to the node
 * Return: success
 */
ssize_t _getnode_index(list_t *hd, list_t *nod)
{
	size_t x = 0;

	while (hd)
	{
		if (hd == nod)
			return (x);
		hd = hd->next;
		x++;
	}
	return (-1);
}


