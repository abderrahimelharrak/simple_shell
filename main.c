#include "shell.h"

/**
 * main - entry pont
 * Return: success
 */

int main(void)
{
	char *ligne;
	char *args[MAX_INP_SIZE / 2 + 1];
	int shouldrun = 1;

	while (shouldrun)
	{
		printf("MonShell> ");
		fflush(stdout);

		ligne = readline();

		int i = 0;
		char *token = strtok(ligne, " \t\n");

		while (token != NULL)
		{
			args[i] = token;
			token = strtok(NULL, " \t\n");
			i++;
		}
		args[i] = NULL;
		if (strcmp(args[0], "exit") == 0)
			shouldrun = 0;
		else
			executecommand(args);
		free(ligne);
	}

	return (0);
}
