/*
** EPITECH PROJECT, 2019
** T3x3
** File description:
** GameEditor.hpp
*/

#pragma once

#include "Game.hpp"

class GameEditor : public Game
{
public:
    GameEditor(RenderWindow &_window);
    void run();

private:
    void createResizeTexture(RenderTexture &renderTexture, const bool &reverse = false);
    void resizeBoard(const IntRect &modif);
    void createVertexArrayColor(const FloatRect &affZone);
    void display() const;
    void onEvent(const Event &event);
    void changeColor(Color &color);
    void changePattern();
    void save();

private:
    SwapPattern swapPattern;
    Texture saveButtonTexture;
    RectangleShape saveButtonSprite;
    RenderTexture extendTexture;
    RectangleShape extendSprite;
    RenderTexture reduceTexture;
    RectangleShape reduceSprite;
    VertexArray vertexArrayColor;
    RenderTexture patternTexture;
    RectangleShape patternSprite;

};
