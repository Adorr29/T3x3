/*
** EPITECH PROJECT, 2019
** T3x3
** File description:
** GameFillBoard.hpp
*/

#pragma once

#include "Game.hpp"

class GameFillBoard : public Game
{
public:
    GameFillBoard(RenderWindow &_window, const Uint32 &size);
    void run();
};
