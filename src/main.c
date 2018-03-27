/*
** EPITECH PROJECT, 2017
** for_norme
** File description:
** main.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "prototype.h"

int main(int nb_arg, char **arg_tab)
{
	size_t size = 3;

	if (nb_arg > 2) {
		char msg[20];

		sprintf(msg, "use: %s [size]\n", arg_tab[0]);
		write(STDERR_FILENO, msg, strlen(msg));
		return (84);
	}
	if (nb_arg == 2) {
		for (size_t i = 0; arg_tab[1][i] != '\0'; i++)
			if (arg_tab[1][i] < '0' || arg_tab[1][i] > '9') {
				char msg[20];

				sprintf(msg, "\"%s\" is not a number\n", arg_tab[1]);
				write(STDERR_FILENO, msg, strlen(msg));
				return (84);
			}
		size = atoi(arg_tab[1]);
	}
	if (size == 0) {
		char *msg = "size can't be 0\n";

		write(STDERR_FILENO, msg, strlen(msg));
		return (84);
	}
	srand(time(NULL));
	return (menu(size));
}
