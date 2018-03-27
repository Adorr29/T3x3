/*
** EPITECH PROJECT, 2017
** T3x3
** File description:
** play.c
*/

#include "prototype.h"

bool play(sfEvent *event, sfRenderWindow *window, map_t *map)
{
	sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(window);
	sfVector2u win_size = sfRenderWindow_getSize(window);
	size_t x;
	size_t y;

	if (mouse_pos.x < 0 || mouse_pos.x >= (int)win_size.x)
		return (false);
	if (mouse_pos.y < 0 || mouse_pos.y >= (int)win_size.y)
		return (false);
	if (event->type == sfEvtMouseButtonPressed)
		if (sfMouse_isButtonPressed(sfMouseLeft)) {
			x = (size_t)mouse_pos.x / (win_size.x / map->size);
			y = (size_t)mouse_pos.y / (win_size.y / map->size);
			map_swaps(map, x, y);
			return (map_full(map));
		}
	return (false);
}
