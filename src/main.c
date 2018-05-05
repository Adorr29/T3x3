/*
** EPITECH PROJECT, 2017
** T3x3
** File description:
** main.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "prototype.h"

int main(int nb_arg, char **arg_tab)
{
	size_t size = 3;

	if (nb_arg > 2) {
		fprintf(stderr, "use: %s [size]\n", arg_tab[0]);
		return (84);
	}
	if (nb_arg == 2) {
		for (size_t i = 0; arg_tab[1][i] != '\0'; i++)
			if (arg_tab[1][i] < '0' || arg_tab[1][i] > '9') {
				fprintf(stderr, "\"%s\" is not a number\n", arg_tab[1]);
				return (84);
			}
		size = atoi(arg_tab[1]);
	}
	if (size == 0) {
		fprintf(stderr, "size can't be 0\n");
		return (84);
	}
	srand(time(NULL));
	return (menu(size));
}
