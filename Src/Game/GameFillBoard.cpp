/*
** EPITECH PROJECT, 2019
** T3x3
** File description:
** GameFillBoard.cpp
*/

#include "Game/GameFillBoard.hpp"

GameFillBoard::GameFillBoard(RenderWindow &_window, const Uint32 &size)
    : Game(_window)
{
    board.create(Vector2u(size, size));
    board.generate();
    winBoard.create(Vector2u(size, size));
    winBoard.fill();
    affZone = FloatRect(Vector2f(0, 0), Vector2f(window.getSize()));
}

void GameFillBoard::run()
{
    while (window.isOpen()) {
        pollEvent();
        window.clear();
        board.aff(window, affZone);
        window.display();
        if (board == winBoard && winSound.getStatus() == SoundSource::Stopped)
            break;
    }
}
