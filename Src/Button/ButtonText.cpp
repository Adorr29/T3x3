/*
** EPITECH PROJECT, 2019
** T3x3
** File description:
** ButtonText.cpp
*/

#include "Button/ButtonText.hpp"

ButtonText::ButtonText()
{
    font.loadFromFile("Resources/Font/Prototype.ttf");
    text.setFont(font);
}

void ButtonText::setPosition(const Vector2f &position)
{
    Button::setPosition(position);
    text.setPosition(position);
}

void ButtonText::setRotation(const float &angle)
{
    Button::setRotation(angle);
    text.setRotation(angle);
}

void ButtonText::setSize(const Vector2f &size)
{
    Button::setSize(size);
    text.setCharacterSize(size.y);
    textSetOrigin();
}

void ButtonText::setString(const string &str)
{
    text.setString(str);
    textSetOrigin();
}

void ButtonText::setColor(const Color &color)
{
    Button::setColor(color);
    text.setFillColor(color);
}

void ButtonText::aff(RenderTarget &window) const
{
    Button::aff(window);
    window.draw(text);
}

void ButtonText::textSetOrigin()
{
    text.setOrigin(0, 0); // easy way
    const Vector2f textPosDiff(text.getGlobalBounds().left - text.getPosition().x, text.getGlobalBounds().top - text.getPosition().y);

    text.setOrigin(text.getGlobalBounds().width / 2.0 + textPosDiff.x, text.getGlobalBounds().height / 2.0 + textPosDiff.y);
}
