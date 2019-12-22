/*
** EPITECH PROJECT, 2019
** T3x3
** File description:
** Game.hpp
*/

#pragma once

#include <SFML/Audio.hpp>
#include "Board.hpp"

class Game
{
public:
    Game(RenderWindow &_window);
    virtual void run() = 0;

protected:
    void pollEvent();

protected:
    RenderWindow &window;
    Board board;
    Board winBoard;
    FloatRect affZone;
    Music winSound; // TODO use Sound
};
