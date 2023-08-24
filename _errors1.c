#include "shell.h"

/**
 * erratoi_ - converts a string to an integer
 * @str: the string to be converted
 * Return: success
 */
int erratoi_(char *str)
{
	int x = 0;
	unsigned long int res = 0;

	if (*str == '+')
		str++;
	for (x = 0;  str[x] != '\0'; x++)
	{
		if (str[x] >= '0' && str[x] <= '9')
		{
			res *= 10;
			res += (str[x] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * print_err - prints an error message
 * @info: the parameter & return info struct
 * @str: string containing specified error type
 * Return: success
 */
void print_err(info_t *info, char *str)
{
	eputs_(info->filename);
	eputs_(": ");
	_printd(info->line_c, STDERR_FILENO);
	eputs_(": ");
	eputs_(info->argumv[0]);
	eputs_(": ");
	eputs_(str);
}

/**
 * _printd - function prints a decimal (integer) number (base 10)
 * @inp: the input
 * @f: the filedescriptor to write
 * Return: success
 */
int _printd(int inp, int f)
{
	int (*_putchar_)(char) = putchar_;
	int x, counter = 0;
	unsigned int _abs_, curr;

	if (f == STDERR_FILENO)
		_putchar_ = eputchar_;
	if (inp < 0)
	{
		_abs_ = -inp;
		_putchar_('-');
		counter++;
	}
	else
		_abs_ = inp;
	curr = _abs_;
	for (x = 1000000000; x > 1; x /= 10)
	{
		if (_abs_ / x)
		{
			_putchar_('0' + curr / x);
			counter++;
		}
		curr %= x;
	}
	_putchar_('0' + curr);
	counter++;

	return (counter);
}

/**
 * _convertnumber - converter function, a clone of itoa
 * @number: number
 * @bas: bas
 * @flag: argument flag
 * Return: success
 */
char *_convertnumber(long int number, int bas, int flag)
{
	static char *t;
	static char buff[50];
	char signe = 0;
	char *str;
	unsigned long x = number;

	if (!(flag & CONVERT_UNSIGNE) && number < 0)
	{
		x = -number;
		signe = '-';

	}
	t = flag & CONVERT_LOWECASE ? "0123456789abcdef" : "0123456789ABCDEF";
	str = &buff[49];
	*str = '\0';

	do	{
		*--str = t[x % bas];
		x /= bas;
	} while (x != 0);

	if (signe)
		*--str = signe;
	return (str);
}

/**
 * _removecomments - function replaces first instance of '#' with '\0'
 * @buff: address of the string to modify
 * Return: success;
 */
void _removecomments(char *buff)
{
	int x;

	for (x = 0; buff[x] != '\0'; x++)
		if (buff[x] == '#' && (!x || buff[x - 1] == ' '))
		{
			buff[x] = '\0';
			break;
		}
}

