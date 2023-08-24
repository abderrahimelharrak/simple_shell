#include "shell.h"

/**
 * myexit_ - exits the shell
 * @info: Struct
 * Return: sccess
 */
int myexit_(info_t *info)
{
	int exit_check;

	if (info->argumv[1])
	{
		exit_check = erratoi_(info->argumv[1]);
		if (exit_check == -1)
		{
			info->stat = 2;
			print_err(info, "Illegal number: ");
			eputs_(info->argumv[1]);
			eputchar_('\n');
			return (1);
		}
		info->error_num = erratoi_(info->argumv[1]);
		return (-2);
	}
	info->error_num = -1;
	return (-2);
}

/**
 * mycd_ - changes the current directory of the process
 * @info: Struct
 * Return: success
 */
int mycd_(info_t *info)
{
	char *s, *dirr, buff[1024];
	int chdirret;

	s = getcwd(buff, 1024);
	if (!s)
		puts_("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argumv[1])
	{
		dirr = getenv_(info, "HOME=");
		if (!dirr)
			chdirret = chdir((dirr = getenv_(info, "PWD=")) ? dirr : "/");
		else
			chdirret = chdir(dirr);
	}
	else if (strcmp_(info->argumv[1], "-") == 0)
	{
		if (!getenv_(info, "OLDPWD="))
		{
			puts_(s);
			putchar_('\n');
			return (1);
		}
		puts_(getenv_(info, "OLDPWD=")), putchar_('\n');
		chdirret = chdir((dirr = getenv_(info, "OLDPWD=")) ? dirr : "/");
	}
	else
		chdirret = chdir(info->argumv[1]);
	if (chdirret == -1)
	{
		print_err(info, "can't cd to ");
		eputs_(info->argumv[1]), eputchar_('\n');
	}
	else
	{
		setenv_(info, "OLDPWD", getenv_(info, "PWD="));
		setenv_(info, "PWD", getcwd(buff, 1024));
	}
	return (0);
}

/**
 * myhelp_ - changes the current directory of the process
 * @info: Struct
 * Return: success
 */
int myhelp_(info_t *info)
{
	char **argarray;

	argarray = info->argumv;
	puts_("help call works. Function not yet implemented \n");
	if (0)
		puts_(*argarray);
	return (0);
}

