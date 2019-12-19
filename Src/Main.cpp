/*
** EPITECH PROJECT, 2019
** T3x3
** File description:
** Main.cpp
*/

#include <iostream>
#include <SFML/Graphics.hpp>
#include "World.hpp"

using namespace std;
using namespace sf;

int main()
{
    RenderWindow window(VideoMode(900, 900), "T3x3", Style::Close);
    World world(3);
    World win(3);

    world.generate();
    win.fill();
    window.setFramerateLimit(30);
    while (window.isOpen()) {
        for (Event event; window.pollEvent(event);) {
            if (event.type == Event::Closed)
                window.close();
            else if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    world.swap(Vector2u(event.mouseButton.x / 300, event.mouseButton.y / 300));
                    if (world == win)
                        window.close();
                }
            }
        }
        window.clear();
        world.aff(window);
        window.display();
    }
    return 0;
}
