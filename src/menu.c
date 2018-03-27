/*
** EPITECH PROJECT, 2017
** for_norme
** File description:
** menu.c
*/

#include <unistd.h>
#include "prototype.h"
#include "map.h"

int menu(size_t size)
{
	sfVideoMode mode = {WINDOW_SIZE, WINDOW_SIZE, WINDOW_BITS_PER_PIXEL};
	sfRenderWindow *window;
	map_t map;
	int game_output;

	window = sfRenderWindow_create(mode, "T3x3", WINDOW_PARAMS, NULL);
	if (!window)
		return (84);
	sfRenderWindow_setFramerateLimit(window, FRAMERATE_LIMIT);
	while (sfRenderWindow_isOpen(window)) {
		map = map_create(size);
		if (map.size == 0)
			break;
		game_output = game(window, &map);
		map_destroy(&map);
		size++;
		game_output ? sleep(1) : 0;
		if (!game_output)
			break;
	}
	sfRenderWindow_destroy(window);
	return (0);
}
