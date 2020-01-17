/*
** EPITECH PROJECT, 2019
** T3x3
** File description:
** MenuChallenge.hpp
*/

#pragma once

#include "Menu/Menu.hpp"

class MenuChallenge : public Menu
{
public:
    MenuChallenge(RenderWindow &_window);
    void run();

private:
    void createButtonList();
    void display() const;

private:
    //
};
