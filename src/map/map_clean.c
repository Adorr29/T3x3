/*
** EPITECH PROJECT, 2017
** T3x3
** File description:
** map_clean.c
*/

#include "map.h"

void map_clean(map_t *map, bool value)
{
	for (size_t i = 0; i < map->size; i++)
		for (size_t j = 0; j < map->size; j++)
			map->tab[i][j] = value;
}
