/*
** EPITECH PROJECT, 2019
** T3x3
** File description:
** ButtonBoard.cpp
*/

#include "Button/ButtonBoard.hpp"

const string &ButtonBoard::getBoardPath() const
{
    return boardPath;
}

void ButtonBoard::setSize(const Vector2f &size)
{
    Button::setSize(size);
    if (board)
        upadteRenderTexture();
}

void ButtonBoard::setBoardPath(const string &_boardPath)
{
    boardPath = _boardPath;
    board = make_unique<Board>(boardPath);
    if (board)
        upadteRenderTexture();
}

void ButtonBoard::setColor(const Color &color)
{
    Button::setColor(color);
    rectangle.setFillColor(color);
}

void ButtonBoard::upadteRenderTexture()
{
    if (renderTexture.getSize() != Vector2u(rectangle.getSize()))
        renderTexture.create(rectangle.getSize().x, rectangle.getSize().y);
    renderTexture.clear(Color::Black);
    board->aff(renderTexture);
    renderTexture.display();
    rectangle.setTexture(&renderTexture.getTexture());
}
