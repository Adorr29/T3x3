/*
** EPITECH PROJECT, 2019
** T3x3
** File description:
** Menu.cpp
*/

#include <unistd.h>
#include "Menu/Menu.hpp"
#include "SoundBox.hpp"

array<array<tuple<float, bool>, 9>, 9> Menu::backgroundGrid;
array<Color, 2> Menu::backgroundColor;
RectangleShape Menu::backgroundMask;

Menu::Menu(RenderWindow &_window)
    : window(_window),
      buttonColor({Color(240, 240, 240), Color(180, 180, 180)})
{
    buttonSound = SoundBox::getInstance().getSound("Button");
    if (backgroundMask.getSize().x == 0) // if backgroundSetup has not been call
        backgroundSetup();
}

Menu::~Menu()
{
    // dont destroy menu if has not finished to playing the sound
    if (buttonSound.getStatus() == SoundSource::Status::Playing) {
        Time durationLeft = buttonSound.getBuffer()->getDuration() - buttonSound.getPlayingOffset();

        usleep(durationLeft.asMicroseconds());
    }
}

void Menu::displayButton() const
{
    for (const auto &buttonPair : buttonMap)
        buttonPair.second->aff(window);
}

void Menu::hoverButton(const Vector2f &mousePos)
{
    for (auto &buttonPair : buttonMap) {
        ButtonPtr &button = buttonPair.second;

        if (button->contains(mousePos))
            button->setColor(buttonColor[1]);
        else
            button->setColor(buttonColor[0]);
    }
}

void Menu::updateBackground()
{
    backgroundGridTransition();
    backgroundSwapDirection();
}

void Menu::displayBackground() const
{
    RectangleShape cellSprite(Vector2f(window.getSize().x / backgroundGrid.size(), window.getSize().y / backgroundGrid.front().size()));
    const Vector2f rectSize(window.getSize().x / (float)backgroundGrid.size(), window.getSize().y / (float)backgroundGrid.front().size());

    cellSprite.setSize(rectSize * (float)0.97);
    cellSprite.setOrigin(cellSprite.getSize() / (float)2);
    for (size_t i = 0; i < backgroundGrid.size(); i++)
        for (size_t j = 0; j < backgroundGrid.front().size(); j++) {
            const float transition = get<0>(backgroundGrid[i][j]);
            Color color0(backgroundColor[0].r * (1 - transition), backgroundColor[0].g * (1 - transition), backgroundColor[0].b * (1 - transition));
            Color color1(backgroundColor[1].r * transition, backgroundColor[1].g * transition, backgroundColor[1].b * transition);
            Color finalColor(color0 + color1);

            cellSprite.setFillColor(finalColor);
            cellSprite.setPosition((i + 0.5) * rectSize.x, (j + 0.5) * rectSize.y);
            window.draw(cellSprite);
        }
    window.draw(backgroundMask);
}

void Menu::backgroundSetup()
{
    for (size_t i = 0; i < backgroundGrid.size(); i++)
        for (size_t j = 0; j < backgroundGrid.front().size(); j++)
            if (rand() % 2)
                backgroundGrid[i][j] = make_tuple(1, 1);
            else
                backgroundGrid[i][j] = make_tuple(0, 0);
    backgroundColor = {Color(50, 50, 50), Color(250, 160, 0)};
    backgroundMask.setSize(Vector2f(window.getSize()));
    backgroundMask.setFillColor(Color(0, 0, 0, 100));
}

void Menu::backgroundGridTransition()
{
    for (size_t i = 0; i < backgroundGrid.size(); i++)
        for (size_t j = 0; j < backgroundGrid.front().size(); j++) {
            float &transition = get<0>(backgroundGrid[i][j]);
            const bool direction = get<1>(backgroundGrid[i][j]);
            const float speed = 0.01;

            if (direction == 1 && transition < 1.0) {
                if (transition + speed >= 1.0)
                    transition = 1.0;
                else
                    transition += speed;
            }
            else if (direction == 0 && transition > 0.0) {
                if (transition - speed <= 0.0)
                    transition = 0.0;
                else
                    transition -= speed;
            }
        }
}

void Menu::backgroundSwapDirection()
{
    if (rand() % 3 == 0) {
        const Vector2u pos(rand() % backgroundGrid.size(), rand() % backgroundGrid.front().size());
        const float transition = get<0>(backgroundGrid[pos.x][pos.y]);
        bool &direction = get<1>(backgroundGrid[pos.x][pos.y]);

        if (transition == direction)
            direction = !direction;
    }
}
