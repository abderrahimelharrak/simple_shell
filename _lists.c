#include "shell.h"

/**
 * _addnode - adds a node to the start of the list
 * @hd: address of pointer to head node
 * @str: str field of node
 * @number: node index used by history
 * Return: success
 */
list_t *_addnode(list_t **hd, const char *str, int number)
{
	list_t *new_hd;

	if (!hd)
		return (NULL);
	new_hd = malloc(sizeof(list_t));
	if (!new_hd)
		return (NULL);
	memset_((void *)new_hd, 0, sizeof(list_t));
	new_hd->num = number;
	if (str)
	{
		new_hd->string = strdup_(str);
		if (!new_hd->string)
		{
			free(new_hd);
			return (NULL);
		}
	}
	new_hd->next = *hd;
	*hd = new_hd;
	return (new_hd);
}

/**
 * _addnode_end - adds a node to the end of the list
 * @hd: address of pointer to head node
 * @str: str field of node
 * @number: node index used by history
 * Return: success
 */
list_t *_addnode_end(list_t **hd, const char *str, int number)
{
	list_t *new_nod, *nod;

	if (!hd)
		return (NULL);

	nod = *hd;
	new_nod = malloc(sizeof(list_t));
	if (!new_nod)
		return (NULL);
	memset_((void *)new_nod, 0, sizeof(list_t));
	new_nod->num = number;
	if (str)
	{
		new_nod->string = strdup_(str);
		if (!new_nod->string)
		{
			free(new_nod);
			return (NULL);
		}
	}
	if (nod)
	{
		while (nod->next)
			nod = nod->next;
		nod->next = new_nod;
	}
	else
		*hd = new_nod;
	return (new_nod);
}

/**
 * _printlist_str - prints only the str element of a list_t linked list
 * @hd: pointer to first node
 * Return: success
 */
size_t _printlist_str(const list_t *hd)
{
	size_t x = 0;

	while (hd)
	{
		puts_(hd->string ? hd->string : "(nil)");
		puts_("\n");
		hd = hd->next;
		x++;
	}
	return (x);
}

/**
 * _deletenode_at_index - deletes node at given index
 * @hd: address of pointer to first node
 * @indx: index of node to delete
 * Return: success
 */
int _deletenode_at_index(list_t **hd, unsigned int indx)
{
	list_t *nod, *prev_nod;
	unsigned int x = 0;

	if (!hd || !*hd)
		return (0);

	if (!indx)
	{
		nod = *hd;
		*hd = (*hd)->next;
		free(nod->string);
		free(nod);
		return (1);
	}
	nod = *hd;
	while (nod)
	{
		if (x == indx)
		{
			prev_nod->next = nod->next;
			free(nod->string);
			free(nod);
			return (1);
		}
		x++;
		prev_nod = nod;
		nod = nod->next;
	}
	return (0);
}

/**
 * _freelist - frees all nodes of a list
 * @hd_ptr: address of pointer to head node
 * Return: success
 */
void _freelist(list_t **hd_ptr)
{
	list_t *nod, *next_nod, *hd;

	if (!hd_ptr || !*hd_ptr)
		return;
	hd = *hd_ptr;
	nod = hd;
	while (nod)
	{
		next_nod = nod->next;
		free(nod->string);
		free(nod);
		nod = next_nod;
	}
	*hd_ptr = NULL;
}

