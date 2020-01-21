/*
** EPITECH PROJECT, 2019
** T3x3
** File description:
** MenuNbSwap.cpp
*/

#include "Menu/MenuNbSwap.hpp"
#include "Game/GameChallenge.hpp"
#include "Button/ButtonText.hpp"
#include "Button/ButtonImage.hpp"
#include "Button/ButtonBoard.hpp"

MenuNbSwap::MenuNbSwap(RenderWindow &_window)
    : Menu(_window),
      nbSwap(3)
{
    createButtonList();
}

void MenuNbSwap::setBoardPath(const string &_boardPath)
{
    boardPath = _boardPath;
    static_cast<ButtonBoard&>(*buttonMap["Board"]).setBoardPath(boardPath);
}

void MenuNbSwap::run()
{
    exit = false;
    while (window.isOpen() && !exit) {
        for (Event event; window.pollEvent(event);) {
            if (event.type == Event::Closed)
                window.close();
            else if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Escape)
                    exit = true;
            }
            else if (event.type == Event::MouseButtonPressed) {
                const Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

                for (auto &buttonPair : buttonMap) {
                    const string &buttonName = buttonPair.first;
                    const ButtonPtr &button = buttonPair.second;

                    if (button->contains(mousePos)) {
                        buttonSound.play();
                        if (buttonName == "Back")
                            exit = true;
                        else if (buttonName == "Start") {
                            GameChallenge(window, nbSwap, boardPath).run();
                            exit = true;
                        }
                        else if (buttonName == "Plus") {
                            nbSwap++;
                            refershButtonNbSwap();
                        }
                        else if (buttonName == "Minus" && nbSwap > 1) {
                            nbSwap--;
                            refershButtonNbSwap();
                        }
                        hoverButton(Vector2f(0, 0)); // for reset button color
                    }
                }
            }
            else if (event.type == Event::MouseMoved) {
                hoverButton(Vector2f(event.mouseMove.x, event.mouseMove.y));
                buttonMap["NbSwap"]->setColor(buttonColor[0]);
                buttonMap["Board"]->setColor(buttonColor[0]);
            }
            else if (event.type == Event::MouseButtonReleased) {
                hoverButton(Vector2f(event.mouseButton.x, event.mouseButton.y));
                buttonMap["NbSwap"]->setColor(buttonColor[0]);
                buttonMap["Board"]->setColor(buttonColor[0]);
            }
        }
        if (!exit) {
            updateBackground();
            window.clear();
            display();
            window.display();
        }
    }
}

void MenuNbSwap::createButtonList()
{
    auto buttonBack = make_unique<ButtonImage>();
    buttonBack->setPosition(Vector2f(50, 50));
    buttonBack->setSize(Vector2f(50, 50));
    buttonBack->setImage("Resources/Texture/Back.png");
    buttonBack->setColor(buttonColor[0]);
    buttonMap["Back"] = move(buttonBack);

    auto buttonStart = make_unique<ButtonText>();
    buttonStart->setPosition(Vector2f(window.getSize().x * 3.0 / 4.0, 800));
    buttonStart->setSize(Vector2f(300, 100));
    buttonStart->setString("Start");
    buttonStart->setColor(buttonColor[0]);
    buttonMap["Start"] = move(buttonStart);

    auto buttonBoard = make_unique<ButtonBoard>();
    buttonBoard->setPosition(Vector2f(window.getSize().x / 2.0, 375));
    buttonBoard->setSize(Vector2f(600, 600));
    buttonBoard->setColor(buttonColor[0]);
    buttonMap["Board"] = move(buttonBoard);

    auto buttonNbSwap = make_unique<ButtonText>();
    buttonNbSwap->setPosition(Vector2f(window.getSize().x / 4.0, 800));
    buttonNbSwap->setSize(Vector2f(200, 100));
    buttonNbSwap->setThickness(0);
    buttonNbSwap->setString(to_string(nbSwap));
    buttonNbSwap->setColor(buttonColor[0]);
    buttonMap["NbSwap"] = move(buttonNbSwap);

    auto buttonPlus = make_unique<ButtonImage>();
    buttonPlus->setPosition(Vector2f(window.getSize().x / 4.0 + 120, 800));
    buttonPlus->setSize(Vector2f(50, 50));
    buttonPlus->setThickness(0);
    buttonPlus->setImage("Resources/Texture/ArrowHead.png");
    buttonPlus->setColor(buttonColor[0]);
    buttonMap["Plus"] = move(buttonPlus);

    auto buttonMinus = make_unique<ButtonImage>();
    buttonMinus->setPosition(Vector2f(window.getSize().x / 4.0 - 120, 800));
    buttonMinus->setRotation(180);
    buttonMinus->setSize(Vector2f(50, 50));
    buttonMinus->setThickness(0);
    buttonMinus->setImage("Resources/Texture/ArrowHead.png");
    buttonMinus->setColor(buttonColor[0]);
    buttonMap["Minus"] = move(buttonMinus);
}

void MenuNbSwap::refershButtonNbSwap()
{
    static_cast<ButtonText&>(*buttonMap["NbSwap"]).setString(to_string(nbSwap));
}

void MenuNbSwap::display() const
{
    displayBackground();
    displayButton();
}
