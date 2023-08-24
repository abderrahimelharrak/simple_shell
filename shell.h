#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INP_SIZE 1024

// Fonction pour lire une ligne de l'entrée standard
char *readline();

// Fonction pour exécuter une commande
void executecommand(char **);
#endif
