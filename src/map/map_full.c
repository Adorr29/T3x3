/*
** EPITECH PROJECT, 2017
** T3x3
** File description:
** map_full.c
*/

#include "map.h"

bool map_full(map_t *map)
{
	for (size_t i = 0; i < map->size; i++)
		for (size_t j = 0; j < map->size; j++)
			if (map->tab[i][j] == false)
				return (false);
	return (true);
}
