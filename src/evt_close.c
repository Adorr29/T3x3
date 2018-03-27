/*
** EPITECH PROJECT, 2017
** for_norme
** File description:
** evt_close.c
*/

#include "prototype.h"

void evt_close(sfEvent *event, sfRenderWindow *window)
{
	event->type == sfEvtClosed ? sfRenderWindow_close(window) : 0;
	if (event->type == sfEvtKeyPressed)
		if (sfKeyboard_isKeyPressed(sfKeyEscape))
			sfRenderWindow_close(window);
}
