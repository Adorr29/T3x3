/*
** EPITECH PROJECT, 2019
** T3x3
** File description:
** MenuClassic.cpp
*/

#include "Menu/MenuClassic.hpp"
#include "Game/GameClassic.hpp"
#include "Button/ButtonText.hpp"
#include "Button/ButtonImage.hpp"

MenuClassic::MenuClassic(RenderWindow &_window)
    : Menu(_window),
      boardSize(5)
{
    createButtonList();
}

void MenuClassic::run()
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
                        else if (buttonName == "Start")
                            GameClassic(window, boardSize).run();
                        else if (buttonName == "SizeUp") {
                            boardSize++;
                            static_cast<ButtonText&>(*buttonMap["BoardSize"]).setString(to_string(boardSize));
                            //
                        }
                        else if (buttonName == "SizeDown" && boardSize > 1) {
                            boardSize--;
                            static_cast<ButtonText&>(*buttonMap["BoardSize"]).setString(to_string(boardSize));
                            //
                        }
                        else if (buttonName == "Infinite")
                            while (true) {
                                GameClassic game(window, boardSize);

                                game.run();
                                if (!game.win()) {
                                    static_cast<ButtonText&>(*buttonMap["BoardSize"]).setString(to_string(boardSize));
                                    break;
                                }
                                boardSize++;
                            }
                        hoverButton(Vector2f(0, 0)); // for reset button color
                    }
                }
            }
            else if (event.type == Event::MouseMoved) {
                hoverButton(Vector2f(event.mouseMove.x, event.mouseMove.y));
                buttonMap["BoardSize"]->setColor(buttonColor[0]);
            }
        }
        updateBackground();
        window.clear();
        display();
        window.display();
    }
}

void MenuClassic::createButtonList()
{
    auto buttonBack = make_unique<ButtonImage>();
    buttonBack->setPosition(Vector2f(50, 50));
    buttonBack->setSize(Vector2f(50, 50));
    buttonBack->setImage("Resources/Texture/Back.png");
    buttonBack->setColor(buttonColor[0]);
    buttonMap["Back"] = move(buttonBack);

    auto buttonStart = make_unique<ButtonText>();
    buttonStart->setPosition(Vector2f(window.getSize().x / 2.0, 650));
    buttonStart->setSize(Vector2f(300, 100));
    buttonStart->setString("Start");
    buttonStart->setColor(buttonColor[0]);
    buttonMap["Start"] = move(buttonStart);

    auto buttonBoardSize = make_unique<ButtonText>();
    buttonBoardSize->setPosition(Vector2f(window.getSize().x / 2.0, 350));
    buttonBoardSize->setSize(Vector2f(300, 200));
    buttonBoardSize->setThickness(0);
    buttonBoardSize->setString(to_string(boardSize));
    buttonBoardSize->setColor(buttonColor[0]);
    buttonMap["BoardSize"] = move(buttonBoardSize);

    auto buttonSizeUp = make_unique<ButtonImage>();
    buttonSizeUp->setPosition(Vector2f(window.getSize().x / 2.0 + 220, 350));
    buttonSizeUp->setSize(Vector2f(100, 100));
    buttonSizeUp->setThickness(0);
    buttonSizeUp->setImage("Resources/Texture/ArrowHead.png");
    buttonSizeUp->setColor(buttonColor[0]);
    buttonMap["SizeUp"] = move(buttonSizeUp);

    auto buttonSizeDown = make_unique<ButtonImage>();
    buttonSizeDown->setPosition(Vector2f(window.getSize().x / 2.0 - 220, 350));
    buttonSizeDown->setRotation(180);
    buttonSizeDown->setSize(Vector2f(100, 100));
    buttonSizeDown->setThickness(0);
    buttonSizeDown->setImage("Resources/Texture/ArrowHead.png");
    buttonSizeDown->setColor(buttonColor[0]);
    buttonMap["SizeDown"] = move(buttonSizeDown);

    auto buttonInfinite = make_unique<ButtonImage>();
    buttonInfinite->setPosition(Vector2f(window.getSize().x / 2.0 + 240, 650));
    buttonInfinite->setSize(Vector2f(100, 100));
    buttonInfinite->setImage("Resources/Texture/Infinite.png");
    buttonInfinite->setColor(buttonColor[0]);
    buttonMap["Infinite"] = move(buttonInfinite);
}

void MenuClassic::display() const
{
    displayBackground();
    displayButton();
}
