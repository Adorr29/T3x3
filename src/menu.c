/*
** EPITECH PROJECT, 2017
** T3x3
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
	map_t *map;
	int game_output;

	window = sfRenderWindow_create(mode, WINDOW_NAME, WINDOW_PARAMS, NULL);
	if (!window)
		return (84);
	sfRenderWindow_setFramerateLimit(window, FRAMERATE_LIMIT);
	while (sfRenderWindow_isOpen(window)) {
		map = map_create(size);
		if (map == NULL)
			return (84);
		map_rand(map);
		game_output = game(window, map);
		map_destroy(map);
		size++;
		game_output ? sleep(1) : 0;
	}
	sfRenderWindow_destroy(window);
	return (0);
}
