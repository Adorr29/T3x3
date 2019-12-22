/*
** EPITECH PROJECT, 2019
** T3x3
** File description:
** Game.cpp
*/

#include "Game/Game.hpp"

Game::Game(RenderWindow &_window)
    : window(_window)
{
    winSound.openFromFile("Resources/Sound/Win.ogg");
}

void Game::pollEvent()
{
    const Vector2f rectSize(affZone.width / board.getSize().x, affZone.height / board.getSize().y);

    for (Event event; window.pollEvent(event);)
        if (event.type == Event::Closed)
            window.close();
        else if (event.type == Event::MouseButtonPressed)
            if (event.mouseButton.button == Mouse::Left)
                if (board != winBoard) {
                    const Vector2u boardPosition((event.mouseButton.x - affZone.left) / rectSize.x, (event.mouseButton.y - affZone.top) / rectSize.y);

                    board.swap(boardPosition);
                    if (board == winBoard)
                        winSound.play();
                }
}
