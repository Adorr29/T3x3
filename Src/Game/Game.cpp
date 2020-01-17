/*
** EPITECH PROJECT, 2019
** T3x3
** File description:
** Game.cpp
*/

#include "Game/Game.hpp"

Game::Game(RenderWindow &_window)
    : window(_window),
      originWindowSize(_window.getSize()),
      exit(false),
      swapLock(false)
{
    swapCallback = [](const Vector2u&){};
    eventCallback = [](const Event&){};
    winSound = SoundBox::getInstance().getSound("Win");
    swapSound = SoundBox::getInstance().getSound("Swap");
    swapSound.setPitch(0.5);
}

bool Game::win() const
{
    return board == winBoard;
}

void Game::pollEvent()
{
    const Vector2f rectSize(affZone.width / board.getSize().x, affZone.height / board.getSize().y);

    for (Event event; window.pollEvent(event);) {
        if (event.type == Event::Closed)
            window.close();
        else if (event.type == Event::KeyPressed) {
            if (event.key.code == Keyboard::Escape)
                exit = true;
        }
        else if (event.type == Event::MouseButtonPressed)
            if (event.mouseButton.button == Mouse::Left)
                if (board != winBoard && !swapLock) {
                    const Vector2u boardPosition((event.mouseButton.x - affZone.left) / rectSize.x, (event.mouseButton.y - affZone.top) / rectSize.y);

                    if (board.swap(boardPosition)) {
                        swapSound.play();
                        swapCallback(boardPosition);
                        if (win())
                            winSound.play();
                    }
                }
        eventCallback(event);
    }
}

void Game::resizeWindow(const Vector2u &size)
{
    window.setSize(size);
    window.setView(View(FloatRect(0, 0, window.getSize().x, window.getSize().y)));
}

void Game::createPatternTexture(RenderTexture &renderTexture, const SwapPattern &swapPattern)
{
    Texture swapTexture;
    Texture originTexture;
    RectangleShape sprite;
    Vector2i min, max;
    Vector2u patternSize;

    for (const Vector2i &one : swapPattern) {
        if (one.x < min.x)
            min.x = one.x;
        else if (one.x > max.x)
            max.x = one.x;
        if (one.y < min.y)
            min.y = one.y;
        else if (one.y > max.y)
            max.y = one.y;
    }
    swapTexture.loadFromFile("Resources/Texture/Swap.png");
    originTexture.loadFromFile("Resources/Texture/Origin.png");
    renderTexture.create(originWindowSize.x / 3, originWindowSize.y / 3);
    renderTexture.clear(Color::Transparent);
    patternSize = Vector2u(max.x - min.x + 1, max.y - min.y + 1);
    sprite.setSize(Vector2f(renderTexture.getSize().x / (float)patternSize.x, renderTexture.getSize().y / (float)patternSize.y));
    for (const Vector2i &one : swapPattern) {
        const Vector2u toSwap(patternSize.x / 2 + one.x, patternSize.y / 2 + one.y);

        sprite.setPosition(toSwap.x * sprite.getSize().x, toSwap.y * sprite.getSize().y);
        sprite.setTexture(&swapTexture);
        renderTexture.draw(sprite);
    }
    sprite.setPosition((patternSize.x / 2) * sprite.getSize().x, (patternSize.y / 2) * sprite.getSize().y);
    sprite.setTexture(&originTexture);
    renderTexture.draw(sprite);
    renderTexture.display();
}
