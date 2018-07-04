/*
** EPITECH PROJECT, 2018
** T3x3
** File description:
** ia.c
*/

#include <stdio.h> //tmp
#include "prototype.h"

static void full_down(map_t *map)
{
	for (size_t j = 0; j < map->size - 1; j++)
		for (size_t i = 0; i < map->size; i++)
			if (map->tab[i][j] == false)
				map_swaps(map, i, j + 1);
}

static bool get_patern(size_t size, bool patern[size][size])
{
	map_t *map = map_create(size);

	if (map == NULL)
		return (true);
	for (size_t i = 0; i < size; i++) {
		map_clean(map, true);
		map_swaps(map, i, 0);
		full_down(map);
		for (size_t j = 0; j < size; j++)
			patern[i][j] = !map->tab[j][size - 1];
	}
	map_destroy(map);
	return (false);
}

static sfVector2i last_swap(map_t *map, bool patern[map->size][map->size])
{
	for (size_t i = 0; i < map->size; i++) {
		bool tmp = true;

		for (size_t j = 0; j < map->size; j++)
			if (patern[i][j] == map->tab[j][map->size - 1]) {
				tmp = false;
				break;
			}
		if (tmp) {
			printf("last_swap %ld\n", i);
			return ((sfVector2i){i, 0});
		}
	}
	return ((sfVector2i){-1, -1});
}

static sfVector2i single_swap(map_t *map, bool patern[map->size][map->size], bool patern_left[map->size])
{
	bool reset = false;

	/*for (size_t i = 0; i < map->size; i++)
		printf("%d ", map->tab[i][map->size - 1]);
		printf("\n");*/
	for (size_t i = 0; i < map->size; reset ? i = 0 : i++) {
		size_t j_save;
		bool tmp = false;

		reset = false;
		for (size_t j = 0; j < map->size; j++)
			if (patern_left[j] && patern[j][i] == true) {
				if (tmp == false) {
					j_save = j;
					tmp = true;
				}
				else {
					tmp = false;
					break;
				}
			}
		if (tmp) {
			if (map->tab[i][map->size - 1]) {
				//printf("anti_single_swap %ld\n", j_save);
				patern_left[j_save] = false;
				reset = true;
			}
			else {
				printf("single_swap %ld\n", j_save);
				return ((sfVector2i){j_save, 0});
			}
		}
	}
	return ((sfVector2i){-1, -1});
}

sfVector2i part1(map_t *map, bool patern[map->size][map->size], bool patern_left[map->size])
{
	sfVector2i pos;
	bool patern_left_cpy[map->size];

	pos = last_swap(map, patern);
	if (pos.x >= 0 && pos.y >= 0)
		return (pos);
	for (size_t i = 0; i < map->size; i++)
		patern_left_cpy[i] = patern_left[i];
	pos = single_swap(map, patern, patern_left_cpy);
	if (pos.x >= 0 && pos.y >= 0) {
		for (size_t j = 0; j < map->size; j++)
			map->tab[j][map->size - 1] ^= patern[pos.x][j];
		patern_left_cpy[pos.x] = false;
	}
	for (size_t i = 0; i < map->size; i++)
		if (patern_left_cpy[i]) {
			for (size_t j = 0; j < map->size; j++)
				map->tab[j][map->size - 1] ^= patern[i][j];
			patern_left_cpy[i] = false;
			printf("passe %ld\n", i);
			pos = part1(map, patern, patern_left_cpy);
			for (size_t j = 0; j < map->size; j++)
				map->tab[j][map->size - 1] ^= patern[i][j];
			patern_left_cpy[i] = true;
			if (pos.x >= 0 && pos.y >= 0) {
				return (pos);
			}
		}
	return ((sfVector2i){-1, -1});
}

static sfVector2i part2(map_t *map)
{
	for (size_t j = 0; j < map->size - 1; j++)
		for (size_t i = 0; i < map->size; i++)
			if (map->tab[i][j] == false)
				return ((sfVector2i){i, j + 1});
	return ((sfVector2i){-1, -1});
}

sfVector2i ia(map_t *map)
{
	map_t *map_cpy = map_copy(map);
	sfVector2i pos;
	bool patern[map->size][map->size];
	bool patern_left[map->size];

	if (map_cpy == NULL)
		return (pos);
	full_down(map_cpy);
	if (map_full(map_cpy)) {
		map_destroy(map_cpy);
		return (part2(map));
	}
	if (get_patern(map->size, patern))
		return (pos);
	for (size_t i = 0; i < map->size; i++)
		patern_left[i] = true;

	for (size_t i = 0; i < map->size; i++) {
		for (size_t j = 0; j < map->size; j++)
			printf("%d ", patern[i][j]);
		printf("\n");
	}
	printf("\n");

	pos = single_swap(map_cpy, patern, patern_left);
	if (pos.x >= 0 && pos.y >= 0)
		return (pos);
	for (size_t i = 0; i < map->size; i++)
			printf("%d ", map_cpy->tab[i][map->size - 1]);
	printf("\nstart\n");
	pos = part1(map_cpy, patern, patern_left);
	map_destroy(map_cpy);
	return (pos);
}
