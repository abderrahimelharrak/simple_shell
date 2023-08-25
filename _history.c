#include "shell.h"

/**
 * _gethistory_file - gets the history file
 * @info: parameter struct
 * Return: success
 */

char *_gethistory_file(info_t *info)
{
	char *buff, *dirr;

	dirr = getenv_(info, "HOME=");
	if (!dirr)
		return (NULL);
	buff = malloc(sizeof(char) * (strlen_(dirr) + strlen_(HIST_FILEE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	strcpy_(buff, dirr);
	strcat_(buff, "/");
	strcat_(buff, HIST_FILEE);
	return (buff);
}

/**
 * _writehistory - creates a file, or appends to an existing file
 * @info: the parameter struct
 * Return: success
 */
int _writehistory(info_t *info)
{
	ssize_t f;
	char *filename = _gethistory_file(info);
	list_t *nod = NULL;

	if (!filename)
		return (-1);

	f = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (f == -1)
		return (-1);
	for (nod = info->historique; nod; nod = nod->next)
	{
		putsfd_(nod->string, f);
		putfd_('\n', f);
	}
	putfd_(BUFF_FLUSH, f);
	close(f);
	return (1);
}

/**
 * _readhistory - reads history from file
 * @info: the parameter struct
 * Return: success
 */
int _readhistory(info_t *info)
{
	int x, laste = 0, line_count = 0;
	ssize_t f, rlen, size = 0;
	struct stat st;
	char *buff = NULL, *filename = _gethistory_file(info);

	if (!filename)
		return (0);

	f = open(filename, O_RDONLY);
	free(filename);
	if (f == -1)
		return (0);
	if (!fstat(f, &st))
		size = st.st_size;
	if (size < 2)
		return (0);
	buff = malloc(sizeof(char) * (size + 1));
	if (!buff)
		return (0);
	rlen = read(f, buff, size);
	buff[size] = 0;
	if (rlen <= 0)
		return (free(buff), 0);
	close(f);
	for (x = 0; x < size; x++)
		if (buff[x] == '\n')
		{
			buff[x] = 0;
			_buildhistory_list(info, buff + laste, line_count++);
			laste = x + 1;
		}
	if (laste != x)
		_buildhistory_list(info, buff + laste, line_count++);
	free(buff);
	info->historycount = line_count;
	while (info->historycount-- >= HIST_MAXX)
		_deletenode_at_index(&(info->historique), 0);
	_renumberhistory(info);
	return (info->historycount);
}

/**
 * _buildhistory_list - adds entry to a history linked list
 * @info: Struct
 * @buff: buffer
 * @line_count: the history linecount
 * Return: success
 */
int _buildhistory_list(info_t *info, char *buff, int line_count)
{
	list_t *nod = NULL;

	if (info->historique)
		nod = info->historique;
	_addnode_end(&nod, buff, line_count);

	if (!info->historique)
		info->historique = nod;
	return (0);
}

/**
 * _renumberhistory - renumbers the history linked list after changes
 * @info: Struct
 * Return: success
 */
int _renumberhistory(info_t *info)
{
	list_t *nod = info->historique;
	int x = 0;

	while (nod)
	{
		nod->num = x++;
		nod = nod->next;
	}
	return (info->historycount = x);
}

