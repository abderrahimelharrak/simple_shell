#include "shell.h"

/**
 * hsh - main shell loop
 * @info: the parameter & return info struct
 * @argv: the argument vector from main()
 * Return: success
 */
int hsh(info_t *info, char **argv)
{
	ssize_t rre = 0;
	int builttin_ret = 0;

	while (rre != -1 && builttin_ret != -2)
	{
		_clearinfo(info);
		if (inter_active(info))
			puts_("$ ");
		eputchar_(BUFF_FLUSH);
		rre = _getinput(info);
		if (rre != -1)
		{
			_setinfo(info, argv);
			builttin_ret = _findbuiltin(info);
			if (builttin_ret == -1)
				_findcmd(info);
		}
		else if (inter_active(info))
			putchar_('\n');
		_freeinfo(info, 0);
	}
	_writehistory(info);
	_freeinfo(info, 1);
	if (!inter_active(info) && info->stat)
		exit(info->stat);
	if (builttin_ret == -2)
	{
		if (info->error_num == -1)
			exit(info->stat);
		exit(info->error_num);
	}
	return (builttin_ret);
}

/**
 * _findbuiltin - finds a builtin command
 * @info: struct
 * Return: success
 */
int _findbuiltin(info_t *info)
{
	int x, _builtin_ret = -1;
	builtin_table builtintabl[] = {
		{"exit", myexit_},
		{"env", myenv_},
		{"help", myhelp_},
		{"history", myhistory_},
		{"setenv", mysetenv_},
		{"unsetenv", myunsetenv_},
		{"cd", mycd_},
		{"alias", myalias_},
		{NULL, NULL}
	};

	for (x = 0; builtintabl[x].type; x++)
		if (strcmp_(info->argumv[0], builtintabl[x].type) == 0)
		{
			info->line_c++;
			_builtin_ret = builtintabl[x].func(info);
			break;
		}
	return (_builtin_ret);
}

/**
 * _findcmd - finds a command in PATH
 * @info: struct
 * Return: success
 */
void _findcmd(info_t *info)
{
	char *pathe = NULL;
	int x, z;

	info->pathe = info->argumv[0];
	if (info->linec_flag == 1)
	{
		info->line_c++;
		info->linec_flag = 0;
	}
	for (x = 0, z = 0; info->argum[x]; x++)
		if (!_isdelim(info->argum[x], " \t\n"))
			z++;
	if (!z)
		return;

	pathe = _findpath(info, getenv_(info, "PATH="), info->argumv[0]);
	if (pathe)
	{
		info->pathe = pathe;
		_forkcmd(info);
	}
	else
	{
		if ((inter_active(info) || getenv_(info, "PATH=")
					|| info->argumv[0][0] == '/') && _iscmd(info, info->argumv[0]))
			_forkcmd(info);
		else if (*(info->argum) != '\n')
		{
			info->stat = 127;
			print_err(info, "not found\n");
		}
	}
}

/**
 * _forkcmd - forks a an exec thread to run cmd
 * @info: struct
 * Return: success
 */
void _forkcmd(info_t *info)
{
	pid_t childpid;

	childpid = fork();
	if (childpid == -1)
	{
		perror("Error:");
		return;
	}
	if (childpid == 0)
	{
		if (execve(info->pathe, info->argumv, _getenviron(info)) == -1)
		{
			_freeinfo(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->stat));
		if (WIFEXITED(info->stat))
		{
			info->stat = WEXITSTATUS(info->stat);
			if (info->stat == 126)
				print_err(info, "Permission denied\n");
		}
	}
}
