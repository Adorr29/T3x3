/*
** EPITECH PROJECT, 2017
** T3x3
** File description:
** map_destroy.c
*/

#include <stdlib.h>
#include "map.h"

void map_destroy(map_t *map)
{
	for (size_t i = 0; i < map->size; i++)
		free(map->tab[i]);
	free(map->tab);
	free(map);
}
