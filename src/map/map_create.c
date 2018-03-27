/*
** EPITECH PROJECT, 2017
** T3x3
** File description:
** map_create.c
*/

#include <stdlib.h>
#include "map.h"

void map_fill(map_t *map)
{
	size_t nb = rand() % (map->size * map->size) + map->size * map->size;

	for (size_t n = 0; n < nb; n++)
		map_swaps(map, rand() % map->size, rand() % map->size);
	map_full(map) ? map_fill(map) : 0;
}

map_t map_create(size_t size)
{
	map_t map = {.size = size};
	map_t error = {.size = 0};

	map.tab = malloc(sizeof(bool *) * size);
	if (map.tab == NULL)
		return (error);
	for (size_t i = 0; i < map.size; i++) {
		map.tab[i] = malloc(sizeof(bool) * size);
		if (map.tab[i] == NULL)
			return (error);
		for (size_t j = 0; j < map.size; j++)
			map.tab[i][j] = true;
	}
	map_fill(&map);
	return (map);
}
