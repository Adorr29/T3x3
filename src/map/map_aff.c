/*
** EPITECH PROJECT, 2017
** T3x3
** File description:
** map_aff.c
*/

#include "map.h"

sfColor get_color(bool tmp)
{
	sfColor fill_color = {FILL_COLOR, 255};
	sfColor empty_color = {EMPTY_COLOR, 255};

	return (tmp ? fill_color : empty_color);
}

void map_aff(sfRenderWindow *window, map_t *map)
{
	sfRectangleShape *rect = sfRectangleShape_create();
	sfVector2u win_size = sfRenderWindow_getSize(window);
	int d = (win_size.x / map->size) / 30;
	int d2 = win_size.x - win_size.x / map->size * map->size;
	sfVector2f size = {.x = win_size.x / map->size - d};

	size.y = win_size.y / map->size - d;
	sfRectangleShape_setSize(rect, size);
	for (size_t i = 0; i < map->size; i++)
		for (size_t j = 0; j < map->size; j++) {
			sfColor color = get_color(map->tab[i][j]);
			sfVector2f pos;

			pos.x = win_size.x / map->size * i + d / 2 + d2 / 2;
			pos.y = win_size.y / map->size * j + d / 2 + d2 / 2;
			sfRectangleShape_setPosition(rect, pos);
			sfRectangleShape_setFillColor(rect, color);
			sfRenderWindow_drawRectangleShape(window, rect, NULL);
		}
	sfRectangleShape_destroy(rect);
}
