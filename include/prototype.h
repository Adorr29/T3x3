/*
** EPITECH PROJECT, 2017
** for_norme
** File description:
** prototype.h
*/

#ifndef PROTOTYPE_H_
#define PROTOTYPE_H_

#include <SFML/Graphics.h>
#include "map.h"

#define WINDOW_SIZE 900
#define WINDOW_BITS_PER_PIXEL 32
#define WINDOW_PARAMS sfClose
#define FRAMERATE_LIMIT 30

int menu(size_t size);
int game(sfRenderWindow *window, map_t *map);
bool play(sfEvent *event, sfRenderWindow *window, map_t *map);
void swaps(map_t *map, sfRenderWindow *window);
bool test_win(map_t *map);
void evt_close(sfEvent *event, sfRenderWindow *window);

#endif
