/*
** EPITECH PROJECT, 2018
** T3x3
** File description:
** map_copy.c
*/

#include "map.h"

map_t *map_copy(map_t *map)
{
	map_t *map_cpy = map_create(map->size);

	if (map_cpy == NULL)
		return (NULL);
	for (size_t i = 0; i < map_cpy->size; i++)
		for (size_t j = 0; j < map_cpy->size; j++) {
			map_cpy->tab[i][j] = map->tab[i][j];
			map_cpy->solve[i][j] = map->solve[i][j];
		}
	map_cpy->help = map->help;
	return (map_cpy);
}
