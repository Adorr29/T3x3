/*
** EPITECH PROJECT, 2019
** T3x3
** File description:
** MenuChallenge.hpp
*/

#pragma once

#include "Menu/Menu.hpp"
#include "Menu/MenuNbSwap.hpp"

class MenuChallenge : public Menu
{
public:
    MenuChallenge(RenderWindow &_window);
    void run();

private:
    void createButtonList();
    void refershButtonBoard();
    void display() const;

private:
    bool exit;
    vector<string> boardPathList;
    const Vector2u pageSize;
    size_t page;
    MenuNbSwap menuNbSwap;
};
