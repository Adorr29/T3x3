/*
** EPITECH PROJECT, 2017
** T3x3
** File description:
** swaps.c
*/

#include "prototype.h"

void swap(bool *tmp)
{
	*tmp ? *tmp = false : (*tmp = true);
}

void map_swaps(map_t *map, size_t x, size_t y)
{
	swap(&map->tab[x][y]);
	x > 0 ? swap(&map->tab[x - 1][y]) : 0;
	x < map->size - 1 ? swap(&map->tab[x + 1][y]) : 0;
	y > 0 ? swap(&map->tab[x][y - 1]) : 0;
	y < map->size - 1 ? swap(&map->tab[x][y + 1]) : 0;
}
