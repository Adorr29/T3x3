/*
** EPITECH PROJECT, 2019
** T3x3
** File description:
** Menu.hpp
*/

#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Button/Button.hpp"

class Menu
{
public:
    Menu(RenderWindow &_window);
    virtual ~Menu();
    virtual void run() = 0;

protected:
    void displayButton() const;
    void hoverButton(const Vector2f &mousePos);
    void updateBackground();
    void displayBackground() const;


private:
    void backgroundSetup();
    void backgroundGridTransition();
    void backgroundSwapDirection();

protected:
    RenderWindow &window;
    map<string, ButtonPtr> buttonMap;
    array<Color, 2> buttonColor;
    Sound buttonSound;

private: // background common for all menu
    static array<array<tuple<float, bool>, 9>, 9> backgroundGrid;
    static array<Color, 2> backgroundColor;
    static RectangleShape backgroundMask;
};

typedef unique_ptr<Menu> MenuPtr;
