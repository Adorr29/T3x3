/*
** EPITECH PROJECT, 2019
** T3x3
** File description:
** GameEditor.cpp
*/

#include <cmath>
#include "Game/GameEditor.hpp"

GameEditor::GameEditor(RenderWindow &_window)
    : Game(_window)
{
    winBoard.create(Vector2u(0, 0));
    board.create(Vector2u(5, 5));
    board.setSwapPattern({{0, 0}});
    board.fill(false);
    affZone = FloatRect(Vector2f(0, 0), Vector2f(window.getSize()));
    eventCallback = bind(&GameEditor::onEvent, this, placeholders::_1);
    swapPattern = CrossSwapPartten;

    saveButtonTexture.loadFromFile("Resources/Texture/Save.png");
    saveButtonSprite.setTexture(&saveButtonTexture);
    saveButtonSprite.setSize(Vector2f(originWindowSize) / (float)5.0);
    saveButtonSprite.setPosition(originWindowSize.x, 0);

    createResizeTexture(extendTexture);
    extendSprite.setTexture(&extendTexture.getTexture());
    extendSprite.setSize(Vector2f(originWindowSize) / (float)5.0);
    extendSprite.setPosition(originWindowSize.x, originWindowSize.y * 2 / 5.0);

    createResizeTexture(reduceTexture, true);
    reduceSprite.setTexture(&reduceTexture.getTexture());
    reduceSprite.setSize(Vector2f(originWindowSize) / (float)5.0);
    reduceSprite.setPosition(originWindowSize.x, originWindowSize.y * 3 / 5.0);

    createVertexArrayColor(FloatRect(originWindowSize.x, originWindowSize.y * 4 / 5.0, originWindowSize.x / 5.0, originWindowSize.y / 5.0));

    createPatternTexture(patternTexture, swapPattern);
    patternSprite.setPosition(originWindowSize.x, originWindowSize.y * 1 / 5.0);
    patternSprite.setSize(Vector2f(originWindowSize) / (float)5);
    patternSprite.setTexture(&patternTexture.getTexture());
}

void GameEditor::run()
{
    resizeWindow(Vector2u(originWindowSize.x * 6 / 5.0, originWindowSize.y));
    while (window.isOpen() && !exit) {
        pollEvent();
        window.clear();
        display();
        window.display();
    }
    resizeWindow(originWindowSize);
}

void GameEditor::createResizeTexture(RenderTexture &renderTexture, const bool &reverse)
{
    const float rotationList[] = {225, 270, 315, 180, -1, 0, 135, 90, 45};
    Texture texture;
    RectangleShape sprite;

    renderTexture.create(originWindowSize.x / 5, originWindowSize.y / 5);
    texture.loadFromFile("Resources/Texture/Arrow.png");
    sprite.setTexture(&texture);
    sprite.setSize(Vector2f(renderTexture.getSize()) / (float)3.0);
    sprite.setOrigin(sprite.getSize() / (float)2.0);
    for (Uint8 i = 0; i < 3; i++)
        for (Uint8 j = 0; j < 3; j++)
            if (i != 1 || j != 1) {
                sprite.setPosition(sprite.getSize().x * (i + 0.5), sprite.getSize().y * (j + 0.5));
                sprite.setRotation(rotationList[i + 3 * j] + (reverse ? 180.0 : 0.0));
                renderTexture.draw(sprite);
            }
    renderTexture.display();
}

void GameEditor::createVertexArrayColor(const FloatRect &affZone)
{
    const array<Color, 2> &colorTab = board.getColor();

    vertexArrayColor.setPrimitiveType(Triangles);
    vertexArrayColor.append(Vertex(Vector2f(affZone.left, affZone.top), colorTab[0]));
    vertexArrayColor.append(Vertex(Vector2f(affZone.left + affZone.width, affZone.top), colorTab[0]));
    vertexArrayColor.append(Vertex(Vector2f(affZone.left, affZone.top + affZone.height), colorTab[0]));
    vertexArrayColor.append(Vertex(Vector2f(affZone.left + affZone.width, affZone.top + affZone.height), colorTab[1]));
    vertexArrayColor.append(Vertex(Vector2f(affZone.left + affZone.width, affZone.top), colorTab[1]));
    vertexArrayColor.append(Vertex(Vector2f(affZone.left, affZone.top + affZone.height), colorTab[1]));
}

void GameEditor::display() const
{
    board.aff(window, affZone);
    window.draw(saveButtonSprite);
    window.draw(extendSprite);
    window.draw(reduceSprite);
    window.draw(patternSprite);
    window.draw(vertexArrayColor);
}

void GameEditor::onEvent(const Event &event)
{
    if (event.type == Event::KeyPressed) {
        if (event.key.code == Keyboard::S && event.key.control == true)
            save();
    }
    else if (event.type == Event::MouseButtonPressed)
        if (event.mouseButton.button == Mouse::Left) {
            const vector<RectangleShape> resizeButtonList = {extendSprite, reduceSprite};
            const Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

            if (saveButtonSprite.getGlobalBounds().contains(mousePos))
                save();
            else if (patternSprite.getGlobalBounds().contains(mousePos))
                changePattern();
            else if (vertexArrayColor.getBounds().contains(mousePos)) {
                const Vector2f mouseRelativePos(mousePos.x - vertexArrayColor.getBounds().left, mousePos.y - vertexArrayColor.getBounds().top);
                array<Color, 2> color = board.getColor();
                bool index = 0;

                if (mouseRelativePos.x + mouseRelativePos.y > (vertexArrayColor.getBounds().width + vertexArrayColor.getBounds().height) / 2.0)
                    index = 1;
                changeColor(color[index]);
                board.setColor(color);
                createVertexArrayColor(FloatRect(originWindowSize.x, originWindowSize.y * 4 / 5.0, originWindowSize.x / 5.0, originWindowSize.y / 5.0));
            }
            else
                for (size_t i = 0; i < resizeButtonList.size(); i++) {
                    const RectangleShape &resizeButton = resizeButtonList[i];

                    if (resizeButton.getGlobalBounds().contains(mousePos)) {
                        const Vector2f mouseRelativePos(mousePos.x - resizeButton.getPosition().x, mousePos.y - resizeButton.getPosition().y);
                        Vector2i back;
                        Vector2i front;

                        if (mouseRelativePos.x < resizeButton.getSize().x * 1 / 3.0)
                            back.x = 1;
                        else if (mouseRelativePos.x > resizeButton.getSize().x * 2 / 3.0)
                            front.x = 1;
                        if (mouseRelativePos.y < resizeButton.getSize().y * 1 / 3.0)
                            back.y = 1;
                        else if (mouseRelativePos.y > resizeButton.getSize().y * 2 / 3.0)
                            front.y = 1;
                        if (&resizeButton == &resizeButtonList[1]) {
                            back *= -1;
                            front *= -1;
                        }
                        board.resize(back, front);
                    }
                }
        }
}

void GameEditor::changeColor(Color &color)
{
    static Image colorTabImage; // static or use a texure
    Texture colorTabTexture;
    RectangleShape colorTabSprite(Vector2f(256 * 2, 256));
    Color newColor = color;
    RectangleShape newColorSprite(Vector2f(colorTabSprite.getSize().y, colorTabSprite.getSize().y));

    if (colorTabImage.getSize().x == 0) { // if is not create
        Color tmpColor = Color::Red;
        array<reference_wrapper<Uint8>, 4> colorOrder = {tmpColor.r, tmpColor.g, tmpColor.b, tmpColor.r};
        size_t x = 0;

        colorTabImage.create(255 * 6, 256);
        for (size_t i = 0; i < 3; i++) {
            for (size_t j = 0; colorOrder[i + 1] < 255; colorOrder[i + 1]++, j++) {
                for (size_t k = 0; k < 256; k++) {
                    Color tmpColor2 = tmpColor;

                    tmpColor2.r *= k / 255.0;
                    tmpColor2.g *= k / 255.0;
                    tmpColor2.b *= k / 255.0;
                    colorTabImage.setPixel(x, 255 - k, tmpColor2);
                }
                x++;
            }
            for (size_t j = 0; colorOrder[i] > 0; colorOrder[i]--, j++) {
                for (size_t k = 0; k < 256; k++) {
                    Color tmpColor2 = tmpColor;

                    tmpColor2.r *= k / 255.0;
                    tmpColor2.g *= k / 255.0;
                    tmpColor2.b *= k / 255.0;
                    colorTabImage.setPixel(x, 255 - k, tmpColor2);
                }
                x++;
            }
        }
    }
    colorTabTexture.create(colorTabImage.getSize().x, colorTabImage.getSize().y);
    colorTabTexture.update(colorTabImage);
    colorTabSprite.setTexture(&colorTabTexture);
    newColorSprite.setOrigin(newColorSprite.getSize().x, 0);
    newColorSprite.setFillColor(newColor);
    const VideoMode videoMode(colorTabSprite.getSize().x + colorTabSprite.getSize().y + 5, colorTabSprite.getSize().y);
    RenderWindow colorWindow(videoMode, "Color", Style::Close);

    newColorSprite.setPosition(colorWindow.getSize().x, 0);
    colorWindow.setFramerateLimit(10); // or 30
    while (colorWindow.isOpen()) {
        for (Event event; colorWindow.pollEvent(event);) {
            if (event.type == Event::Closed)
                colorWindow.close();
            else if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Escape)
                    colorWindow.close();
                else if (event.key.code == Keyboard::Enter) {
                    color = newColor;
                    colorWindow.close();
                }
            }
            else if (event.type == Event::MouseButtonPressed || (event.type == Event::MouseMoved && Mouse::isButtonPressed(Mouse::Left))) {
                Vector2f mousePos;

                if (event.type == Event::MouseButtonPressed)
                    mousePos = Vector2f(event.mouseButton.x, event.mouseButton.y);
                else if (event.type == Event::MouseMoved && Mouse::isButtonPressed(Mouse::Left))
                    mousePos = Vector2f(event.mouseMove.x, event.mouseMove.y);
                if (colorTabSprite.getGlobalBounds().contains(mousePos)) {
                    const Vector2f mouseRelativePos(mousePos.x - colorTabSprite.getPosition().x, mousePos.y - colorTabSprite.getPosition().y);
                    const Vector2f scale(colorTabImage.getSize().x / (float)colorTabSprite.getSize().x, colorTabImage.getSize().y / (float)colorTabSprite.getSize().y);

                    newColor = colorTabImage.getPixel(mouseRelativePos.x * scale.x, mouseRelativePos.y * scale.y);
                    newColorSprite.setFillColor(newColor);
                }
            }
        }
        colorWindow.clear();
        colorWindow.draw(colorTabSprite);
        colorWindow.draw(newColorSprite);
        colorWindow.display();
    }
}

void GameEditor::changePattern()
{
    const vector<SwapPattern> swapPatternList = {CrossSwapPartten, SquareSwapPartten};
    vector<RenderTexture> patternTextureList(swapPatternList.size());
    RectangleShape patternSprite(Vector2f(200, 200));
    const size_t gridSize = ceil(sqrt(swapPatternList.size()));
    const VideoMode videoMode(patternSprite.getSize().x * gridSize, patternSprite.getSize().y * gridSize);
    RenderWindow changeWindow(videoMode, "Pattern", Style::Close);

    for (size_t i = 0; i < patternTextureList.size(); i++)
        createPatternTexture(patternTextureList[i], swapPatternList[i]);
    patternSprite.setOutlineThickness(1);
    patternSprite.setOutlineColor(Color(200, 200, 200));
    changeWindow.setFramerateLimit(10); // or 30
    while (changeWindow.isOpen()) {
        for (Event event; changeWindow.pollEvent(event);) {
            if (event.type == Event::Closed)
                changeWindow.close();
            else if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Escape)
                    changeWindow.close();
            }
            else if (event.type == Event::MouseButtonPressed)
                if (event.mouseButton.button == Mouse::Left) {
                    const Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);
                    const Vector2i selectPos(mousePos.x / patternSprite.getSize().x, mousePos.y / patternSprite.getSize().y);
                    const size_t select = selectPos.x + selectPos.y * gridSize;

                    if (select < swapPatternList.size()) {
                        swapPattern = swapPatternList[select];
                        createPatternTexture(patternTexture, swapPattern);
                        changeWindow.close();
                    }
                }
        }
        changeWindow.clear();
        for (size_t i = 0; i < patternTextureList.size(); i++) {
            patternSprite.setTexture(&patternTextureList[i].getTexture());
            patternSprite.setPosition(i % gridSize * patternSprite.getSize().x, i / gridSize * patternSprite.getSize().y);
            changeWindow.draw(patternSprite);
        }
        changeWindow.display();
    }
}

void GameEditor::save()
{
    RenderWindow saveWindow(VideoMode(400, 150), "Save", Style::Close);
    string fileName;
    Font font;
    Text text;
    size_t clock;

    saveWindow.setFramerateLimit(10); // or 30
    font.loadFromFile("Resources/Font/Prototype.ttf");
    text.setFont(font);
    text.setCharacterSize(60);
    text.setPosition(10, 10);
    while (saveWindow.isOpen()) {
        for (Event event; saveWindow.pollEvent(event);) {
            if (event.type == Event::Closed)
                saveWindow.close();
            else if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Escape)
                    saveWindow.close();
                else if (event.key.code == Keyboard::Enter) {
                    board.setSwapPattern(swapPattern);
                    if (board.save("Resources/Board/" + fileName))
                        saveWindow.close();
                    else
                        fileName = "Save Failed";
                    board.setSwapPattern({{0, 0}});
                }
            }
            else if (event.type == Event::TextEntered) {
                if (event.text.unicode == '\b') {
                    if (!fileName.empty())
                        fileName = fileName.substr(0, fileName.size() - 1);
                }
                else {
                    fileName += event.text.unicode;
                    clock = 0;
                }
            }
        }
        if (fileName.empty()) {
            text.setFillColor(Color(127, 127, 127));
            text.setString("File Name");
        }
        else {
            text.setFillColor(Color::White);
            text.setString(fileName + (clock < 10 ? "_" : ""));
            clock++;
            if (clock >= 20)
                clock = 0;
        }
        saveWindow.clear();
        saveWindow.draw(text);
        saveWindow.display();
    }
}
