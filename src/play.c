/*
** EPITECH PROJECT, 2017
** T3x3
** File description:
** play.c
*/

#include <stdlib.h>
#include "prototype.h"

static void player(sfVector2i mouse_pos, sfRenderWindow *window, map_t *map)
{
	sfVector2u win_size = sfRenderWindow_getSize(window);
	size_t x;
	size_t y;

	if (mouse_pos.x < 0 || (unsigned int)mouse_pos.x >= win_size.x)
		return;
	if (mouse_pos.y < 0 || (unsigned int)mouse_pos.y >= win_size.y)
		return;
	x = (size_t)mouse_pos.x / (win_size.x / map->size);
	y = (size_t)mouse_pos.y / (win_size.y / map->size);
	map_swaps(map, x, y);
}

static void help(map_t *map)
{
	if (map->help.x < 0 || map->help.y < 0) {
		size_t nb = 0;
		sfVector2i tmp[map->size * map->size];

		for (size_t i = 0; i < map->size; i++)
			for (size_t j = 0; j < map->size; j++)
				if (map->solve[i][j])
					tmp[nb++] = (sfVector2i){i, j};
		map->help = tmp[rand() % nb];
		//map->help = ia(map);
	}
	else
		map_swaps(map, map->help.x, map->help.y);
}

bool play(sfEvent *event, sfRenderWindow *window, map_t *map)
{
	if (event->type == sfEvtMouseButtonPressed)
		if (event->mouseButton.button == sfMouseLeft) {
			sfVector2i mouse_pos;

			mouse_pos.x = event->mouseButton.x;
			mouse_pos.y = event->mouseButton.y;
			player(mouse_pos, window, map);
		}
	if (event->type == sfEvtKeyPressed)
		if (event->key.code == sfKeyH)
			help(map);
	return (map_full(map));
}
