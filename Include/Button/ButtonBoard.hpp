/*
** EPITECH PROJECT, 2019
** T3x3
** File description:
** ButtonBoard.hpp
*/

#pragma once

#include "Button.hpp"
#include "Board.hpp"

class ButtonBoard : public Button
{
public:
    const string &getBoardPath() const;
    void setSize(const Vector2f &size);
    void setBoardPath(const string &_boardPath);
    void setColor(const Color &color);

private:
    void upadteRenderTexture();

private:
    string boardPath;
    unique_ptr<Board> board;
    RenderTexture renderTexture;
};
