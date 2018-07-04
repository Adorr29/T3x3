/*
** EPITECH PROJECT, 2017
** T3x3
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
#define HELP_COLOR 255, 0, 0

typedef struct {
	size_t size;
	bool **tab;
	bool **solve;
	sfVector2i help;
} map_t;

map_t *map_create(size_t size);
map_t *map_copy(map_t *map);
void map_destroy(map_t *map);
void map_aff(sfRenderWindow *window, map_t *map);
void map_swaps(map_t *map, size_t x, size_t y);
bool map_full(map_t *map);
void map_clean(map_t *map, bool value);
void map_rand(map_t *map);

#endif
