/*
** EPITECH PROJECT, 2019
** T3x3
** File description:
** Main.cpp
*/

#include <iostream> // tmp ?
#include <SFML/Graphics.hpp>
#include "Game/GameClassic.hpp"
#include "Game/GameChallenge.hpp"
#include "Game/GameEditor.hpp"


class Button
{
public:
    Button();
    void setPosition(const Vector2f &position);
    void setSize(const Vector2f &size);
    void setString(const string &str);
    void setColor(const Color &color);
    void aff(RenderTarget &window) const;
    bool contains(const Vector2f &point) const;

private:
    void textSetOrigin();

private:
    RectangleShape rectangle;
    Font font;
    Text text;
};

Button::Button()
{
    font.loadFromFile("Resources/Font/Prototype.ttf");
    text.setFont(font);
    rectangle.setFillColor(Color::Transparent);
    rectangle.setOutlineThickness(10);
}

void Button::setPosition(const Vector2f &position)
{
    rectangle.setPosition(position);
    text.setPosition(position);
}

void Button::setSize(const Vector2f &size)
{
    rectangle.setSize(size);
    text.setCharacterSize(size.y);
    rectangle.setOrigin(size / (float)2);
    textSetOrigin();
}

void Button::setString(const string &str)
{
    text.setString(str);
    textSetOrigin();
}

void Button::setColor(const Color &color)
{
    rectangle.setOutlineColor(color);
    text.setFillColor(color);
}

void Button::aff(RenderTarget &window) const
{
    window.draw(rectangle);
    window.draw(text);
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

void Button::textSetOrigin()
{
    text.setOrigin(0, 0); // easy way
    const Vector2f textPosDiff(text.getGlobalBounds().left - text.getPosition().x, text.getGlobalBounds().top - text.getPosition().y);

    text.setOrigin(text.getGlobalBounds().width / 2.0 + textPosDiff.x, text.getGlobalBounds().height / 2.0 + textPosDiff.y);
}

class Menu
{
public:
    Menu();
    void run();

private:
    void createButtonList();
    void swapDirection();
    void gridTransition();
    void displayBackground();
    void display();

private:
    RenderWindow window;
    array<array<tuple<float, bool>, 9>, 9> backgroundGrid;
    array<Color, 2> color;
    RectangleShape mask;
    Font titleFont;
    Text title;
    array<Button, 4> buttonList;
    //array<Button, 4> buttonCallback; // TODO ?
    array<Color, 2> buttonColor;
};

Menu::Menu()
    : window(VideoMode(900, 900), "T3x3", Style::Close),
      color({Color(50, 50, 50), Color(250, 160, 0)}),
      buttonColor({Color(240, 240, 240), Color(180, 180, 180)})
{
    window.setFramerateLimit(30);
    mask.setSize(Vector2f(window.getSize()));
    mask.setFillColor(Color(0, 0, 0, 100));
    for (size_t i = 0; i < backgroundGrid.size(); i++)
        for (size_t j = 0; j < backgroundGrid.front().size(); j++)
            if (rand() % 2)
                backgroundGrid[i][j] = make_tuple(1, 1);
            else
                backgroundGrid[i][j] = make_tuple(0, 0);
    titleFont.loadFromFile("Resources/Font/SacredHertz.otf");
    title.setString("T3x3");
    title.setFont(titleFont);
    title.setCharacterSize(250);
    title.setOrigin(title.getGlobalBounds().width / 2.0, 0);
    title.setPosition(window.getSize().x / 2.0, 0);
    title.setFillColor(buttonColor[0]);
    createButtonList();
}

void Menu::createButtonList()
{
    const array<string, 4> buttonString = {"Classic", "Challenge", "Editor", "Exit"};

    for (size_t i = 0; i < buttonList.size(); i++) {
        buttonList[i].setPosition(Vector2f(window.getSize().x / 2.0, 150 * i + 350));
        buttonList[i].setSize(Vector2f(450, 100));
        buttonList[i].setString(buttonString[i]);
        buttonList[i].setColor(buttonColor[0]);
    }
}

void Menu::run()
{
    while (window.isOpen()) {
        for (Event event; window.pollEvent(event);) {
            if (event.type == Event::Closed)
                window.close();
            else if (event.type == Event::MouseButtonPressed) {
                const Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

                for (size_t i = 0; i < buttonList.size(); i++)
                    if (buttonList[i].contains(mousePos)) {
                        unique_ptr<Game> game;

                        // TODO add sub menu
                        if (i == 0)
                            game = make_unique<GameClassic>(window, 5);
                        if (i == 1)
                            game = make_unique<GameChallenge>(window, 3);
                        if (i == 2)
                            game = make_unique<GameEditor>(window);
                        else if (i == 3)
                            window.close();
                        if (game)
                            game->run();
                    }
            }
            else if (event.type == Event::MouseMoved) {
                const Vector2f mousePos(event.mouseMove.x, event.mouseMove.y);

                for (Button &button : buttonList)
                    if (button.contains(mousePos))
                        button.setColor(buttonColor[1]);
                    else
                        button.setColor(buttonColor[0]);
            }
        }
        swapDirection();
        gridTransition();
        window.clear();
        display();
        window.display();
    }
}

void Menu::swapDirection()
{
    if (rand() % 3 == 0) {
        const Vector2u pos(rand() % backgroundGrid.size(), rand() % backgroundGrid.front().size());
        const float transition = get<0>(backgroundGrid[pos.x][pos.y]);
        bool &direction = get<1>(backgroundGrid[pos.x][pos.y]);

        if (transition == direction)
            direction = !direction;
    }
}

void Menu::gridTransition()
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

void Menu::displayBackground()
{
    RectangleShape cellSprite(Vector2f(window.getSize().x / backgroundGrid.size(), window.getSize().y / backgroundGrid.front().size()));
    const Vector2f rectSize(window.getSize().x / (float)backgroundGrid.size(), window.getSize().y / (float)backgroundGrid.front().size());

    cellSprite.setSize(rectSize * (float)0.97);
    cellSprite.setOrigin(cellSprite.getSize() / (float)2);
    for (size_t i = 0; i < backgroundGrid.size(); i++)
        for (size_t j = 0; j < backgroundGrid.front().size(); j++) {
            const float transition = get<0>(backgroundGrid[i][j]);
            Color color0(color[0].r * (1 - transition), color[0].g * (1 - transition), color[0].b * (1 - transition));
            Color color1(color[1].r * transition, color[1].g * transition, color[1].b * transition);
            Color finalColor(color0 + color1);

            cellSprite.setFillColor(finalColor);
            cellSprite.setPosition((i + 0.5) * rectSize.x, (j + 0.5) * rectSize.y);
            window.draw(cellSprite);
        }
}

void Menu::display()
{
    displayBackground();
    window.draw(mask);
    window.draw(title);
    for (const Button &button : buttonList)
        button.aff(window);
}

int main()
{
    srand(time(nullptr));
    Menu menu;

    menu.run();

    /*//unique_ptr<Game> game = make_unique<GameEditor>(window);
    unique_ptr<Game> game = make_unique<GameClassic>(window, 5);
    //unique_ptr<Game> game = make_unique<GameChallenge>(window, 3);

    game->run();*/

    return 0;
}
