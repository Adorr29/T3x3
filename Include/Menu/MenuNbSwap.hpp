/*
** EPITECH PROJECT, 2019
** T3x3
** File description:
** MenuNbSwap.hpp
*/

#pragma once

#include "Menu/Menu.hpp"
#include "Board.hpp"

class MenuNbSwap : public Menu
{
public:
    MenuNbSwap(RenderWindow &_window);
    void setBoardPath(const string &_boardPath);
    void run();

private:
    void createButtonList();
    void refershButtonNbSwap();
    void display() const;

private:
    bool exit;
    string boardPath;
    size_t nbSwap;
};
