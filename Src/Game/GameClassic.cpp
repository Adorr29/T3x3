/*
** EPITECH PROJECT, 2019
** T3x3
** File description:
** GameClassic.cpp
*/

#include "Game/GameClassic.hpp"

GameClassic::GameClassic(RenderWindow &_window, const Uint32 &size)
    : Game(_window)
{
    board.create(Vector2u(size, size));
    board.generate();
    winBoard.create(Vector2u(size, size));
    winBoard.fill();
    affZone = FloatRect(Vector2f(0, 0), Vector2f(window.getSize()));
}

void GameClassic::run()
{
    while (window.isOpen() && !exit) {
        pollEvent();
        window.clear();
        board.aff(window, affZone);
        window.display();
        if (board == winBoard && winSound.getStatus() == SoundSource::Stopped)
            break;
    }
}
