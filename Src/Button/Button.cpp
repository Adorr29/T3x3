/*
** EPITECH PROJECT, 2019
** T3x3
** File description:
** Button.cpp
*/

#include "Button/Button.hpp"

Button::Button()
{
    rectangle.setFillColor(Color::Transparent);
    rectangle.setOutlineThickness(10);
}

void Button::setPosition(const Vector2f &position)
{
    rectangle.setPosition(position);
}

void Button::setRotation(const float &angle)
{
    rectangle.setRotation(angle);
}

void Button::setSize(const Vector2f &size)
{
    rectangle.setSize(size);
    rectangle.setOrigin(size / (float)2);
}

void Button::setThickness(const float &thickness)
{
    rectangle.setOutlineThickness(thickness);
}

void Button::setColor(const Color &color)
{
    rectangle.setOutlineColor(color);
}

void Button::aff(RenderTarget &window) const
{
    window.draw(rectangle);
}

bool Button::contains(const Vector2f &point) const
{
    const FloatRect bounds = rectangle.getGlobalBounds();

    if (point.x < bounds.left)
        return false;
    if (point.x >= bounds.left + bounds.width)
        return false;
    if (point.y < bounds.top)
        return false;
    if (point.y >= bounds.top + bounds.height)
        return false;
    return true;
}
