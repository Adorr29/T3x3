/*
** EPITECH PROJECT, 2017
** for_norme
** File description:
** map.h
*/

#ifndef MAP_H_
#define MAP_H_

#include <SFML/Graphics.h>
#include <stddef.h>
#include <stdbool.h>

#define FILL_COLOR 250, 160, 0
#define EMPTY_COLOR 50, 50, 50

typedef struct {
	size_t size;
	bool **tab;
} map_t;

map_t map_create(size_t size);
void map_destroy(map_t *map);
void map_aff(sfRenderWindow *window, map_t *map);
void map_swaps(map_t *map, size_t x, size_t y);
bool map_full(map_t *map);

#endif
