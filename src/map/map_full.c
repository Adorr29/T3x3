/*
** EPITECH PROJECT, 2017
** T3x3
** File description:
** map_full.c
*/

#include "map.h"

bool map_full(map_t *map)
{
	bool full = true;

	for (size_t i = 0; i < map->size; i++)
		for (size_t j = 0; j < map->size; j++)
			map->tab[i][j] == false ? full = false : 0;
	return (full);
}
