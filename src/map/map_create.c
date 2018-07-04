/*
** EPITECH PROJECT, 2017
** T3x3
** File description:
** map_create.c
*/

#include <stdlib.h>
#include "map.h"

static bool **malloc_2b(size_t size, bool fill)
{
	bool **tab;

	tab = malloc(sizeof(bool *) * size);
	if (tab == NULL)
		return (NULL);
	for (size_t i = 0; i < size; i++) {
		tab[i] = malloc(sizeof(bool) * size);
		if (tab[i] == NULL)
			return (NULL);
		for (size_t j = 0; j < size; j++)
			tab[i][j] = fill;
	}
	return (tab);
}

map_t *map_create(size_t size)
{
	map_t *map = malloc(sizeof(map_t));

	if (map == NULL)
		return (NULL);
	map->size = size;
	map->tab = malloc_2b(map->size, true);
	map->solve = malloc_2b(map->size, false);
	map->help = (sfVector2i){-1, -1};
	return (map);
}
