/*
** EPITECH PROJECT, 2019
** T3x3
** File description:
** MenuClassic.hpp
*/

#pragma once

#include "Menu/Menu.hpp"

class MenuClassic : public Menu
{
public:
    MenuClassic(RenderWindow &_window);
    void run();

private:
    void createButtonList();
    void refreshButtonBoardSize();
    void display() const;

private:
    bool exit;
    Uint32 boardSize;
};
