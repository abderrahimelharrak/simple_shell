#include "shell.h"

/**
 * readline - fonction to read a line from SIOPUT
 * Return:  success
 */

char *readline()
{
	char *ligne = NULL;
	size_t buffsize = 0;

	getline(&ligne, &buffsize, stdin);
	return (ligne);
}

/**
 * executecommand - foction to execute a command
 * @args: a string
 * Return: success
 */

void executecommand(char **args)
{
	pid_t pid, wpid;
	int state;

	pid = fork();
	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			perror("Erreur d'exécution");
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("Erreur de fork");
	}

	else
	{
		do {
			wpid = waitpid(pid, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}
}
