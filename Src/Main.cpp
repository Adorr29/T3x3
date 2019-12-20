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
    World win(world.getSize());

    world.generate();
    win.fill();
    window.setFramerateLimit(30);
    while (window.isOpen()) {
        for (Event event; window.pollEvent(event);) {
            if (event.type == Event::Closed)
                window.close();
            else if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    world.swap(Vector2u(event.mouseButton.x / (window.getSize().x / world.getSize().x), event.mouseButton.y / (window.getSize().y / world.getSize().y)));
                    if (world == win)
                        window.close();
                }
                else
                    world.save("save");
            }
        }
        window.clear();
        world.aff(window);
        window.display();
    }
    return 0;
}
