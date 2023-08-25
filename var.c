#include "shell.h"

/**
 * _ischain - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buff: the char buffer
 * @ptr: address of current position
 * Return: success
 */
int _ischain(info_t *info, char *buff, size_t *ptr)
{
	size_t y = *ptr;

	if (buff[y] == '|' && buff[y + 1] == '|')
	{
		buff[y] = 0;
		y++;
		info->cmd_buff_type = COMD_OR;
	}
	else if (buff[y] == '&' && buff[y + 1] == '&')
	{
		buff[y] = 0;
		y++;
		info->cmd_buff_type = COMD_AND;
	}
	else if (buff[y] == ';')
	{
		buff[y] = 0;
		info->cmd_buff_type = COMD_CHAIN;
	}
	else
		return (0);
	*ptr = y;
	return (1);
}

/**
 * _checkchain - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buff: the char buffer
 * @ptr: address of current position in buf
 * @x: starting position in buf
 * @leng: length of buf
 * Return: success
 */
void _checkchain(info_t *info, char *buff, size_t *ptr, size_t x, size_t leng)
{
	size_t y = *ptr;

	if (info->cmd_buff_type == COMD_AND)
	{
		if (info->stat)
		{
			buff[x] = 0;
			y = leng;
		}
	}
	if (info->cmd_buff_type == COMD_OR)
	{
		if (!info->stat)
		{
			buff[x] = 0;
			y = leng;
		}
	}

	*ptr = y;
}

/**
 * _replacealias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 * Return:success
 */
int _replacealias(info_t *info)
{
	int x;
	list_t *nod;
	char *ptr;

	for (x = 0; x < 10; x++)
	{
		nod = _nodestarts_with(info->aliass, info->argumv[0], '=');
		if (!nod)
			return (0);
		free(info->argumv[0]);
		ptr = strchr_(nod->string, '=');
		if (!ptr)
			return (0);
		ptr = strdup_(ptr + 1);
		if (!ptr)
			return (0);
		info->argumv[0] = ptr;
	}
	return (1);
}

/**
 * _replacevars - replaces vars in the tokenized string
 * @info: the parameter struct
 * Return: success
 */
int _replacevars(info_t *info)
{
	int x = 0;
	list_t *nod;

	for (x = 0; info->argumv[x]; x++)
	{
		if (info->argumv[x][0] != '$' || !info->argumv[x][1])
			continue;

		if (!strcmp_(info->argumv[x], "$?"))
		{
			_replacestring(&(info->argumv[x]),
					strdup_(_convertnumber(info->stat, 10, 0)));
			continue;
		}
		if (!strcmp_(info->argumv[x], "$$"))
		{
			_replacestring(&(info->argumv[x]),
					strdup_(_convertnumber(getpid(), 10, 0)));
			continue;
		}
		nod = _nodestarts_with(info->envv, &info->argumv[x][1], '=');
		if (nod)
		{
			_replacestring(&(info->argumv[x]),
					strdup_(strchr_(nod->string, '=') + 1));
			continue;
		}
		_replacestring(&info->argumv[x], strdup_(""));

	}
	return (0);
}

/**
 * _replacestring - replaces string
 * @old_str: address of old string
 * @new_str: new string
 * Return: success
 */
int _replacestring(char **old_str, char *new_str)
{
	free(*old_str);
	*old_str = new_str;
	return (1);
}


