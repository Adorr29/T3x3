/*
** EPITECH PROJECT, 2019
** T3x3
** File description:
** GameChallenge.cpp
*/

#include "Game/GameChallenge.hpp"
#include "Utility/Globpp.hpp"
#include "Error.hpp"

GameChallenge::GameChallenge(RenderWindow &_window, const size_t &_nbSwap, const string &fileName)
    : Game(_window),
      nbSwap(_nbSwap),
      reset(false)
{
    if (fileName.empty())
        loadRandomBoard();
    else if (fileName.back() == '/')
        loadRandomBoard(fileName);
    else
        winBoard.load(fileName);
    board = winBoard;
    board.randomSwap(nbSwap);
    affZone = FloatRect(Vector2f(0, 0), Vector2f(window.getSize()));
    winBoardAffZone = FloatRect(Vector2f(window.getSize().x, 0), Vector2f(window.getSize()) / (float)3);
    createPatternTexture(patternTexture, board.getSwapPattern());
    patternSprite.setPosition(originWindowSize.x, originWindowSize.y / 3.0);
    patternSprite.setSize(Vector2f(originWindowSize) / (float)3);
    patternSprite.setTexture(&patternTexture.getTexture());
    swapCallback = bind(&GameChallenge::onSwap, this, placeholders::_1);
    font.loadFromFile("Resources/Font/Prototype.ttf");
    text.setFont(font);
    text.setCharacterSize(window.getSize().y / 3.0);
    text.setPosition(window.getSize().x * 7 / 6.0, window.getSize().y * 5 / 6.0);
    refreshNbSwapLeft();
    errorSound = SoundBox::getInstance().getSound("Error");
}

void GameChallenge::run()
{
    resizeWindow(Vector2u(originWindowSize.x * 4 / 3.0, originWindowSize.y));
    while (window.isOpen() && !exit) {
        resetBoard();
        pollEvent();
        window.clear();
        display();
        window.display();
        if (board == winBoard && winSound.getStatus() == SoundSource::Stopped)
            break;
    }
    resizeWindow(originWindowSize);
}

void GameChallenge::loadRandomBoard(const string &dirName)
{
    const vector<string> fileNameList = globpp(dirName + "/*");

    if (fileNameList.empty())
        throw ERROR("Directory \"" + dirName + "\" is empty");
    winBoard.load(fileNameList[rand() % fileNameList.size()]);
}

size_t GameChallenge::getNbSwapLeft() const
{
    return nbSwap - swapList.size();
}

void GameChallenge::refreshNbSwapLeft()
{
    text.setString(to_string(getNbSwapLeft()));
    text.setOrigin(0, 0); // easy way
    const Vector2f textPosDiff(text.getGlobalBounds().left - text.getPosition().x, text.getGlobalBounds().top - text.getPosition().y);

    text.setOrigin(text.getGlobalBounds().width / 2.0 + textPosDiff.x, text.getGlobalBounds().height / 2.0 + textPosDiff.y);
}

void GameChallenge::resetBoard()
{
    static size_t clock = 0;

    if (getNbSwapLeft() == 0 && board != winBoard && errorSound.getStatus() == SoundSource::Stopped)
        reset = true;
    if (!reset)
        return;
    if (clock >= 5) {
        board.swap(swapList.back());
        swapList.pop_back();
        refreshNbSwapLeft();
        if (swapList.empty()) {
            swapLock = false;
            reset = false;
        }
        clock = 0;
    }
    else
        clock++;
}

void GameChallenge::display() const
{
    board.aff(window, affZone);
    winBoard.aff(window, winBoardAffZone);
    window.draw(patternSprite);
    window.draw(text);
}

void GameChallenge::onSwap(const Vector2u &position)
{
    swapList.push_back(position);
    refreshNbSwapLeft();
    if (getNbSwapLeft() == 0 && board != winBoard) {
        errorSound.play();
        swapLock = true;
    }
}
