/*
** EPITECH PROJECT, 2019
** T3x3
** File description:
** ButtonImage.hpp
*/

#pragma once

#include "Button.hpp"

class ButtonImage : public Button
{
public:
    void setColor(const Color &color);
    void setImage(const string &fileName);

private:
    Texture texture;
};
