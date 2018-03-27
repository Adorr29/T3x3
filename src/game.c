/*
** EPITECH PROJECT, 2017
** for_norme
** File description:
** game.c
*/

#include "prototype.h"

int game(sfRenderWindow *window, map_t *map)
{
	sfEvent event;
	bool win = false;

	while (sfRenderWindow_isOpen(window) && win == false) {
		while (sfRenderWindow_pollEvent(window, &event)) {
			evt_close(&event, window);
			!win ? win = play(&event, window, map) : 0;
		}
		sfRenderWindow_clear(window, sfBlack);
		map_aff(window, map);
		sfRenderWindow_display(window);
	}
	return (win);
}
