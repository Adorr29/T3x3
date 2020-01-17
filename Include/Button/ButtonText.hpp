/*
** EPITECH PROJECT, 2019
** T3x3
** File description:
** ButtonText.hpp
*/

#pragma once

#include "Button.hpp"

//using namespace std; // TODO supr

class ButtonText : public Button
{
public:
    ButtonText();
    void setPosition(const Vector2f &position);
    void setRotation(const float &angle); // TOOD (Doesn't work)
    void setSize(const Vector2f &size);
    void setString(const string &str);
    void setColor(const Color &color);
    void aff(RenderTarget &window) const;

private:
    void textSetOrigin();

private:
    Font font; // TODO create FontBox
    Text text;
};
