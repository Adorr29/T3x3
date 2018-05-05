/*
** EPITECH PROJECT, 2018
** T3x3
** File description:
** ia.c
*/

#include "prototype.h"

static void full_down(map_t *map)
{
	for (size_t j = 0; j < map->size - 1; j++)
		for (size_t i = 0; i < map->size; i++)
			if (map->tab[i][j] == false)
				map_swaps(map, i, j + 1);
}

sfVector2i ia(map_t *map)
{
	map_t *map_cpy = map_copy(map);
	sfVector2i pos = {-1, -1};

	if (map_cpy == NULL)
		return (pos);
	//
	map_destroy(map_cpy);
	return (pos);
}
