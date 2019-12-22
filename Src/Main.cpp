/*
** EPITECH PROJECT, 2019
** T3x3
** File description:
** Main.cpp
*/

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game/GameFillBoard.hpp"

using namespace std;
using namespace sf;

int main()
{
    RenderWindow window(VideoMode(900, 900), "T3x3", Style::Close);

    unique_ptr<Game> game = make_unique<GameFillBoard>(window, 3);

    game->run();

    return 0;
}
