/*
** EPITECH PROJECT, 2019
** T3x3
** File description:
** GameClassic.hpp
*/

#pragma once

#include "Game.hpp"

class GameClassic : public Game
{
public:
    GameClassic(RenderWindow &_window, const Uint32 &size);
    void run();
};
