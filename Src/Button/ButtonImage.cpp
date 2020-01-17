/*
** EPITECH PROJECT, 2019
** T3x3
** File description:
** ButtonImage.cpp
*/

#include "Button/ButtonImage.hpp"
#include "Error.hpp"

void ButtonImage::setColor(const Color &color)
{
    Button::setColor(color);
    rectangle.setFillColor(color);
}

void ButtonImage::setImage(const string &fileName)
{
    if (!texture.loadFromFile(fileName))
        throw ERROR("\"" + fileName + "\" can not be laod");
    texture.setSmooth(true);
    rectangle.setTexture(&texture);
    rectangle.setFillColor(Color::White);
}
