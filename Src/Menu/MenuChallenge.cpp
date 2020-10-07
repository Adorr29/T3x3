/*
** EPITECH PROJECT, 2019
** T3x3
** File description:
** MenuChallenge.cpp
*/

#include "Menu/MenuChallenge.hpp"
#include "Game/GameChallenge.hpp"
#include "Button/ButtonImage.hpp"
#include "Button/ButtonBoard.hpp"

MenuChallenge::MenuChallenge(RenderWindow &_window)
    : Menu(_window),
      pageSize(3, 3),
      page(0),
      menuNbSwap(_window)
{
    createButtonList();
}

void MenuChallenge::run()
{
    boardPathList = globpp("Resources/Board/*", true);
    refershButtonBoard();
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

                    if (button->isVisible() && button->contains(mousePos)) {
                        buttonSound.play();
                        if (buttonName == "Back")
                            exit = true;
                        else if (buttonName == "Random")
                            GameChallenge(window, rand() % 4 + 1).run();
                        else if (buttonName == "Infinite") {
                            const size_t sizeMin = 4;
                            const size_t sizeMax = 6;
                            const size_t nbGameByStep = 2;
                            size_t nbGame = 0;
                            size_t size = sizeMin;
                            size_t swap = 1;

                            while (true) {
                                string sizeStr = to_string(size);
                                string fileName = "Resources/Board/" + sizeStr + "x" + sizeStr + "/";
                                GameChallenge game(window, swap, fileName);

                                game.run();
                                if (!game.win())
                                    break;
                                nbGame++;
                                if (nbGame >= nbGameByStep) {
                                    nbGame = 0;
                                    size++;
                                    if (size > sizeMax) {
                                        size = sizeMin;
                                        swap++;
                                    }
                                }
                            }
                        }
                        else if (buttonName == "PrevPage") {
                            if (page > 0) {
                                page--;
                                refershButtonBoard();
                            }
                        }
                        else if (buttonName == "NextPage") {
                            size_t nbPage = boardPathList.size() / (pageSize.x * pageSize.y);

                            if (nbPage * pageSize.x * pageSize.y < boardPathList.size())
                                nbPage++;
                            if (page + 1 < nbPage) {
                                page++;
                                refershButtonBoard();
                            }
                        }
                        else if (buttonName.find("Board") == 0) {
                            const ButtonBoard &buttonBoard = static_cast<ButtonBoard&>(*button);

                            menuNbSwap.setBoardPath(buttonBoard.getBoardPath());
                            menuNbSwap.run();
                        }
                        hoverButton(Vector2f(0, 0)); // for reset button color
                    }
                }
            }
            else if (event.type == Event::MouseMoved)
                hoverButton(Vector2f(event.mouseMove.x, event.mouseMove.y));
            else if (event.type == Event::MouseButtonReleased)
                hoverButton(Vector2f(event.mouseButton.x, event.mouseButton.y));
        }
        updateBackground();
        window.clear();
        display();
        window.display();
    }
}

void MenuChallenge::createButtonList()
{
    auto buttonBack = make_unique<ButtonImage>();
    buttonBack->setPosition(Vector2f(50, 50));
    buttonBack->setSize(Vector2f(50, 50));
    buttonBack->setImage("Resources/Texture/Back.png");
    buttonBack->setColor(buttonColor[0]);
    buttonMap["Back"] = move(buttonBack);

    auto buttonRandom = make_unique<ButtonImage>();
    buttonRandom->setPosition(Vector2f(250, 50));
    buttonRandom->setSize(Vector2f(50, 50));
    buttonRandom->setImage("Resources/Texture/Dice.png");
    buttonRandom->setColor(buttonColor[0]);
    buttonMap["Random"] = move(buttonRandom);

    auto buttonInfinite = make_unique<ButtonImage>();
    buttonInfinite->setPosition(Vector2f(350, 50));
    buttonInfinite->setSize(Vector2f(50, 50));
    buttonInfinite->setImage("Resources/Texture/Infinite.png");
    buttonInfinite->setColor(buttonColor[0]);
    buttonMap["Infinite"] = move(buttonInfinite);

    auto buttonPrevPage = make_unique<ButtonImage>();
    buttonPrevPage->setPosition(Vector2f(35, window.getSize().y / 2.0));
    buttonPrevPage->setRotation(180);
    buttonPrevPage->setSize(Vector2f(100, 200));
    buttonPrevPage->setThickness(0);
    buttonPrevPage->setImage("Resources/Texture/ArrowHead.png");
    buttonPrevPage->setColor(buttonColor[0]);
    buttonMap["PrevPage"] = move(buttonPrevPage);

    auto buttonNextPage = make_unique<ButtonImage>();
    buttonNextPage->setPosition(Vector2f(window.getSize().x - 35, window.getSize().y / 2.0));
    buttonNextPage->setSize(Vector2f(100, 200));
    buttonNextPage->setThickness(0);
    buttonNextPage->setImage("Resources/Texture/ArrowHead.png");
    buttonNextPage->setColor(buttonColor[0]);
    buttonMap["NextPage"] = move(buttonNextPage);

    for (size_t i = 0; i < pageSize.x; i++)
        for (size_t j = 0; j < pageSize.y; j++) {
            auto buttonBoard = make_unique<ButtonBoard>();
            buttonBoard->setPosition(Vector2f((i - (pageSize.x - 1) / 2.0) * 250 + window.getSize().x / 2.0, (j - (pageSize.y - 1) / 2.0) * 250 + window.getSize().y / 2.0));
            buttonBoard->setSize(Vector2f(200, 200));
            buttonBoard->setColor(buttonColor[0]);
            buttonMap["Board" + to_string(i) + "_" + to_string(j)] = move(buttonBoard);
        }
}

void MenuChallenge::refershButtonBoard()
{
    for (size_t i = 0; i < pageSize.x; i++)
        for (size_t j = 0; j < pageSize.y; j++) {
            const size_t index = i + j * pageSize.x + page * pageSize.x * pageSize.y;
            const string buttonName = "Board" + to_string(i) + "_" + to_string(j);
            ButtonBoard &button = static_cast<ButtonBoard&>(*buttonMap[buttonName]);

            if (index < boardPathList.size()) {
                button.setBoardPath(boardPathList[index]);
                button.show();
            }
            else
                button.hide();
        }
}

void MenuChallenge::display() const
{
    displayBackground();
    displayButton();
}
