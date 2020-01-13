/*
** EPITECH PROJECT, 2019
** T3x3
** File description:
** Game.hpp
*/

#pragma once

#include <functional>
#include <SFML/Audio.hpp>
#include "Board.hpp"

class Game
{
public:
    Game(RenderWindow &_window);
    virtual ~Game() = default;
    virtual void run() = 0;

protected:
    void pollEvent();
    void resizeWindow(const Vector2u &size);
    void createPatternTexture(RenderTexture &renderTexture, const SwapPattern &swapPattern);

protected:
    RenderWindow &window;
    Vector2u originWindowSize;
    bool exit;
    bool swapLock;
    Board board;
    Board winBoard;
    FloatRect affZone;
    Music winSound; // TODO use Sound
    function<void(const Vector2u&)> swapCallback;
    function<void(const Event&)> eventCallback;
};
