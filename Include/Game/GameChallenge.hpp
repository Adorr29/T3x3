/*
** EPITECH PROJECT, 2019
** T3x3
** File description:
** GameChallenge.hpp
*/

#pragma once

#include "Game.hpp"

class GameChallenge : public Game
{
public:
    GameChallenge(RenderWindow &_window, const size_t &_nbSwap, const string &fileName = "");
    void run();

private:
    void loadRandomBoard(const string &dirName = "Resources/Board");
    size_t getNbSwapLeft() const;
    void refreshNbSwapLeft();
    void resetBoard();
    void display() const;
    void onSwap(const Vector2u &position);

private:
    RenderTexture patternTexture;
    RectangleShape patternSprite;
    Font font;
    Text text;
    FloatRect winBoardAffZone;
    const Vector2u windowSizeSave;
    size_t nbSwap;
    bool reset;
    vector<Vector2u> swapList;
    Music errorSound; // TODO use Sound
};
