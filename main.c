#include "shell.h"

/**
 * main - entry point
 * @argc: arg count
 * @argv: arg vector
 * Return: 0 on success, 1 on error
 */
int main(int argc, char **argv)
{
	info_t inf[] = { INF_INIT };
	int f = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (f)
			: "r" (f));

	if (argc == 2)
	{
		f = open(argv[1], O_RDONLY);
		if (f == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				eputs_(argv[0]);
				eputs_(": 0: Can't open ");
				eputs_(argv[1]);
				eputchar_('\n');
				eputchar_(BUFF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		inf->readfiled = f;
	}
	_populateenv_list(inf);
	_readhistory(inf);
	hsh(inf, argv);
	return (EXIT_SUCCESS);
}

