#include "shell.h"

/**
 * main - entry point
 * @argc: argument
 * @argv: argument vecteur
 * Return: success
 */
void main(int argc, char *argv[])
{
	printf("Program name is: %s\n", argv[0]);
	if (argc < 2)
		printf("No argument passed through command line.\n");
	else
		printf("First argument is: %s\n", argv[1]);
}
