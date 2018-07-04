/*
** EPITECH PROJECT, 2017
** T3x3
** File description:
** map_rand.c
*/

#include <stdlib.h>
#include "map.h"

void map_rand(map_t *map)
{
	size_t nb = rand() % (map->size * map->size) + map->size * map->size;

	map_clean(map, true);
	for (size_t n = 0; n < nb; n++)
		map_swaps(map, rand() % map->size, rand() % map->size);
	map_full(map) ? map_rand(map) : 0;
}
