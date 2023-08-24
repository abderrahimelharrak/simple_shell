
#include "shell.h"

/**
 * _inputbuf - buffers chained commands
 * @info: parameter struct
 * @buff: address of buffer
 * @length: address of len var
 * Return: success
 */
ssize_t _inputbuf(info_t *info, char **buff, size_t *length)
{
	ssize_t rtr = 0;
	size_t length_p = 0;

	if (!*length)
	{
		free(*buff);
		*buff = NULL;
		signal(SIGINT, sigintHandler_);
#if USE_GETLINE
		rtr = getline(buff, &length_p, stdin);
#else
		rtr = getline_(info, buff, &length_p);
#endif
		if (rtr > 0)
		{
			if ((*buff)[rtr - 1] == '\n')
			{
				(*buff)[rtr - 1] = '\0';
				rtr--;
			}
			info->linec_flag = 1;
			_removecomments(*buff);
			_buildhistory_list(info, *buff, info->historycount++);
			if (strchr_(*buff, ';'))
			{
				*length = rtr;
				info->cmd_buff = buff;
			}
		}
	}
	return (rtr);
}

/**
 * _getinput - gets a line minus the newline
 * @info: parameter struct
 * Return: success
 */
ssize_t _getinput(info_t *info)
{
	static char *buff;
	static size_t x, y, length;
	ssize_t rtr = 0;
	char **buff_p = &(info->argum), *ptr;

	putchar_(BUFF_FLUSH);
	rtr = _inputbuf(info, &buff, &length);
	if (rtr == -1)
		return (-1);
	if (length)
	{
		y = x;
		ptr = buff + x;

		_checkchain(info, buff, &y, x, length);
		while (y < length)
		{
			if (_ischain(info, buff, &y))
				break;
			y++;
		}

		x = y + 1;
		if (x >= length)
		{
			x = length = 0;
			info->cmd_buff_type = CMD_NOR;
		}

		*buff_p = ptr;
		return (strlen_(ptr));
	}

	*buff_p = buff;
	return (rtr);
}

/**
 * _readbuf - reads a buffer
 * @info: parameter struct
 * @buff: buffer
 * @x: size
 * Return: success
 */
ssize_t _readbuf(info_t *info, char *buff, size_t *x)
{
	ssize_t rtr = 0;

	if (*x)
		return (0);
	rtr = read(info->readfiled, buff, READ_BUFF_SIZE);
	if (rtr >= 0)
		*x = rtr;
	return (rtr);
}

/**
 * getline_ - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer
 * Return: success
 */
int getline_(info_t *info, char **ptr, size_t *length)
{
	static char buff[READ_BUFF_SIZE];
	static size_t x, len;
	size_t z;
	ssize_t rtr = 0, str = 0;
	char *p = NULL, *new_p = NULL, *ctr;

	p = *ptr;
	if (p && length)
		str = *length;
	if (x == len)
		x = len = 0;

	rtr = _readbuf(info, buff, &len);
	if (rtr == -1 || (rtr == 0 && len == 0))
		return (-1);

	ctr = strchr_(buff + x, '\n');
	z = ctr ? 1 + (unsigned int)(ctr - buff) : len;
	new_p = realloc_(p, str, str ? str + z : z + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (str)
		strncat_(new_p, buff + x, z - x);
	else
		strncpy_(new_p, buff + x, z - x + 1);

	str += z - x;
	x = z;
	p = new_p;

	if (length)
		*length = str;
	*ptr = p;
	return (str);
}

/**
 * sigintHandler_ - blocks ctrl-C
 * @signum: the signal number
 * Return: success
 */
void sigintHandler_(__attribute__((unused))int signum)
{
	puts_("\n");
	puts_("$ ");
	putchar_(BUFF_FLUSH);
}

