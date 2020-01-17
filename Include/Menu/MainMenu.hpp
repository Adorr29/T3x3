/*
** EPITECH PROJECT, 2019
** T3x3
** File description:
** MainMenu.hpp
*/

#pragma once

#include "Menu/Menu.hpp"

class MainMenu : public Menu
{
public:
    MainMenu(RenderWindow &_window);
    void run();

private:
    void createButtonList();
    void display();

private:
    Font titleFont;
    Text title;
    map<string, MenuPtr> menuMap;
};
