/*
** EPITECH PROJECT, 2019
** T3x3
** File description:
** Game.hpp
*/

#pragma once

#include <functional>
#include "Board.hpp"
#include "SoundBox.hpp"

class Game
{
public:
    Game(RenderWindow &_window);
    virtual ~Game() = default;
    virtual void run() = 0;
    bool win() const;

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
    Sound winSound;
    Sound swapSound;
    function<void(const Vector2u&)> swapCallback;
    function<void(const Event&)> eventCallback;
};
