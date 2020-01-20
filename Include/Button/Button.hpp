/*
** EPITECH PROJECT, 2019
** T3x3
** File description:
** Button.hpp
*/

#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Button
{
public:
    Button();
    Button(const Button &button) = delete;
    virtual ~Button() = default;
    const bool &isVisible() const;
    virtual void setPosition(const Vector2f &position);
    virtual void setRotation(const float &angle);
    virtual void setSize(const Vector2f &size);
    void setThickness(const float &thickness);
    virtual void setColor(const Color &color);
    virtual void aff(RenderTarget &window) const;
    bool contains(const Vector2f &point) const;
    void hide();
    void show();

protected:
    RectangleShape rectangle;

private:
    bool visible;
};

typedef unique_ptr<Button> ButtonPtr;
