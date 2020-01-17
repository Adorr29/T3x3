/*
** EPITECH PROJECT, 2019
** T3x3
** File description:
** MainMenu.cpp
*/

#include "Menu/MainMenu.hpp"
#include "Menu/MenuClassic.hpp"
#include "Menu/MenuChallenge.hpp"
#include "Game/GameEditor.hpp"
#include "Button/ButtonText.hpp"
#include "Game/GameChallenge.hpp" // tmp

MainMenu::MainMenu(RenderWindow &_window)
    : Menu(_window)
{
    window.setFramerateLimit(30);
    titleFont.loadFromFile("Resources/Font/SacredHertz.otf");
    title.setString("T3x3");
    title.setFont(titleFont);
    title.setCharacterSize(250);
    title.setOrigin(title.getGlobalBounds().width / 2.0, 0);
    title.setPosition(window.getSize().x / 2.0, 0);
    title.setFillColor(buttonColor[0]);
    createButtonList();
    menuMap["Classic"] = make_unique<MenuClassic>(_window);
    //menuMap["Challenge"] = make_unique<MenuChallenge>(_window)); // TODO
}

void MainMenu::run()
{
    while (window.isOpen()) {
        for (Event event; window.pollEvent(event);) {
            if (event.type == Event::Closed)
                window.close();
            else if (event.type == Event::MouseButtonPressed) {
                const Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

                for (auto &buttonPair : buttonMap) {
                    const string &buttonName = buttonPair.first;
                    const ButtonPtr &button = buttonPair.second;

                    if (button->contains(mousePos)) {
                        buttonSound.play();
                        unique_ptr<Game> game; // tmp

                        // TODO add sub menu
                        if (buttonName == "Classic")
                            menuMap["Classic"]->run();
                        else if (buttonName == "Challenge")
                            game = make_unique<GameChallenge>(window, 3);
                        else if (buttonName == "Editor")
                            GameEditor(window).run();
                        else if (buttonName == "Exit")
                            window.close();
                        if (game)
                            game->run();
                        hoverButton(Vector2f(0, 0));
                    }
                }
            }
            else if (event.type == Event::MouseMoved)
                hoverButton(Vector2f(event.mouseMove.x, event.mouseMove.y));
        }
        updateBackground();
        window.clear();
        display();
        window.display();
    }
}

void MainMenu::createButtonList()
{
    const array<string, 4> buttonString = {"Classic", "Challenge", "Editor", "Exit"};

    for (size_t i = 0; i < buttonString.size(); i++) {
        auto button = make_unique<ButtonText>();

        button->setPosition(Vector2f(window.getSize().x / 2.0, 150 * i + 350));
        button->setSize(Vector2f(450, 100));
        button->setString(buttonString[i]);
        button->setColor(buttonColor[0]);
        buttonMap[buttonString[i]] = move(button);
    }
}

void MainMenu::display()
{
    displayBackground();
    window.draw(title);
    displayButton();
}
