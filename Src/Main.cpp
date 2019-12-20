/*
** EPITECH PROJECT, 2019
** T3x3
** File description:
** Main.cpp
*/

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Board.hpp"

using namespace std;
using namespace sf;

int main()
{
    RenderWindow window(VideoMode(900, 900), "T3x3", Style::Close);
    Board board(3);
    Board win(board.getSize());

    board.generate();
    win.fill();
    window.setFramerateLimit(30);
    while (window.isOpen()) {
        for (Event event; window.pollEvent(event);) {
            if (event.type == Event::Closed)
                window.close();
            else if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    board.swap(Vector2u(event.mouseButton.x / (window.getSize().x / board.getSize().x), event.mouseButton.y / (window.getSize().y / board.getSize().y)));
                    if (board == win)
                        window.close();
                }
                else
                    board.save("save");
            }
        }
        window.clear();
        board.aff(window);
        window.display();
    }
    return 0;
}
