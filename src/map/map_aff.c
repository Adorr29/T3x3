/*
** EPITECH PROJECT, 2017
** T3x3
** File description:
** map_aff.c
*/

#include <stdlib.h>
#include "map.h"

static sfColor get_color(bool tmp)
{
	sfColor fill_color = {FILL_COLOR, 255};
	sfColor empty_color = {EMPTY_COLOR, 255};

	return (tmp ? fill_color : empty_color);
}

void map_aff(sfRenderWindow *window, map_t *map)
{
	sfRectangleShape *rect = sfRectangleShape_create();
	sfVector2u window_size = sfRenderWindow_getSize(window);
	int d = (window_size.x / map->size) / 30;
	int d2 = window_size.x - window_size.x / map->size * map->size;
	sfVector2f size = {.x = window_size.x / map->size - d};
	static float angle = 0;
	static int for_fun = -1;

	size.y = window_size.y / map->size - d;
	sfRectangleShape_setSize(rect, size);
	for (size_t i = 0; i < map->size; i++)
		for (size_t j = 0; j < map->size; j++) {
			sfColor color = get_color(map->tab[i][j]);
			sfVector2f pos;

			pos.x = window_size.x / map->size * i + d / 2 + d2 / 2;
			pos.y = window_size.y / map->size * j + d / 2 + d2 / 2;
			sfRectangleShape_setPosition(rect, pos);
			sfRectangleShape_setFillColor(rect, color);
			sfRenderWindow_drawRectangleShape(window, rect, NULL);
		}
	if (map->help.x >= 0 && map->help.y >= 0) {
		sfVector2f pos;

		pos.x = window_size.x / map->size * map->help.x + d / 2 + d2 / 2 + size.x / 2;
		pos.y = window_size.y / map->size * map->help.y + d / 2 + d2 / 2 + size.y / 2;
		size = (sfVector2f){size.x * 0.75, size.y * 0.75};
		sfRectangleShape_setSize(rect, size);
		sfRectangleShape_setOrigin(rect, (sfVector2f){size.x / 2, size.y / 2});
		sfRectangleShape_setOutlineThickness(rect, size.x / 50);
		sfRectangleShape_setPosition(rect, pos);
		sfRectangleShape_setRotation(rect, angle);
		sfRectangleShape_setOutlineColor(rect, (sfColor){HELP_COLOR, 255});
		sfRectangleShape_setFillColor(rect, sfTransparent);
		sfRenderWindow_drawRectangleShape(window, rect, NULL);
		if (for_fun == 0) {
			sfRectangleShape_rotate(rect, -2 * angle);
			sfRenderWindow_drawRectangleShape(window, rect, NULL);
		}
		else if (for_fun == 1) {
			sfRectangleShape_rotate(rect, 45);
			sfRenderWindow_drawRectangleShape(window, rect, NULL);
		}
		else if (for_fun == 2)
			for (size_t i = 0; i < 4; i++) {
				sfRectangleShape_rotate(rect, angle);
				sfRenderWindow_drawRectangleShape(window, rect, NULL);
			}
		else
			for_fun = rand() % 3;
		angle += 0.5;
	}
	sfRectangleShape_destroy(rect);
}
