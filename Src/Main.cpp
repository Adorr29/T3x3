/*
** EPITECH PROJECT, 2019
** T3x3
** File description:
** Main.cpp
*/

#include <iostream> // tmp ?
#include "Menu/MainMenu.hpp"

int main()
{
    srand(time(nullptr));
    RenderWindow window(VideoMode(900, 900), "T3x3", Style::Close);
    MainMenu menu(window);

    menu.run();

    return 0;
}
