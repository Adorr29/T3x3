/*
** EPITECH PROJECT, 2019
** T3x3
** File description:
** Board.cpp
*/

#include <iostream>
#include <fstream>
#include "Board.hpp"
#include "Error.hpp"

Board::Board()
    : color({Color(50, 50, 50), Color(250, 160, 0)}),
      swapPattern(CrossSwapPartten)
{
}

Board::Board(const Uint32 &_size)
    : Board(Vector2u(_size, _size))
{
}

Board::Board(const Vector2u &_size)
    : Board()
{
    create(_size);
}

Board::Board(const string &fileName)
{
    if (!load(fileName))
        throw ERROR("Load failed");
}

Board::Board(const Board &board)
{
    operator=(board);
}

Board::~Board()
{
    destroy();
}

const Vector2u &Board::getSize() const
{
    return size;
}

const bool *const *Board::getTab() const
{
    return tab;
}

const array<Color, 2> &Board::getColor() const
{
    return color;
}

const SwapPattern &Board::getSwapPattern() const
{
    return swapPattern;
}

void Board::setColor(const array<Color, 2> &_color)
{
    color = _color;
}

void Board::setSwapPattern(const SwapPattern &_swapPattern)
{
    swapPattern = _swapPattern;
}

void Board::fill(const bool &state)
{
    for (Uint32 i = 0; i < size.x; i++)
        for (Uint32 j = 0; j < size.y; j++)
            tab[i][j] = state;
}

void Board::generate(const Uint32 &seed)
{
    bool haveSwap = false;

    fill();
    srand(seed);
    for (Uint32 i = 0; i < size.x; i++)
        for (Uint32 j = 0; j < size.y; j++)
            if (rand() % 2) {
                swap(Vector2u(i, j));
                haveSwap = true;
            }
    if (!haveSwap)
        generate(seed + 1);
}

void Board::randomSwap(const size_t &nbSwap, const Uint32 &seed)
{
    vector<Vector2u> caseList(size.x * size.y);
    size_t n = 0;

    srand(seed);
    for (Uint32 i = 0; i < size.x; i++)
        for (Uint32 j = 0; j < size.y; j++)
            caseList[n++] = Vector2u(i, j);
    for (size_t i = 0; i < nbSwap && i < caseList.size(); i++) {
        const Uint32 index = rand() % caseList.size();

        swap(caseList[index]);
        caseList.erase(caseList.begin() + index);
    }
}

bool Board::swap(const Vector2u &position)
{
    if (position.x >= size.x || position.y >= size.y)
        return false;
    for (const Vector2i &one : swapPattern) {
        const Vector2u toSwap(position.x + one.x, position.y + one.y);

        if (toSwap.x < size.x && toSwap.y < size.y)
            tab[toSwap.x][toSwap.y] = !tab[toSwap.x][toSwap.y];
    }
    return true;
}

void Board::aff(RenderTarget &window, FloatRect affZone) const
{
    if (affZone == FloatRect(0, 0, 0, 0))
        affZone = FloatRect(Vector2f(0, 0), Vector2f(window.getSize()));
    const Vector2f rectSize(affZone.width / (float)size.x, affZone.height / (float)size.y);
    RectangleShape rectangle;

    rectangle.setSize(rectSize * (float)0.97);
    rectangle.setOrigin(rectangle.getSize() / (float)2);
    for (Uint32 i = 0; i < size.x; i++)
        for (Uint32 j = 0; j < size.y; j++) {
            rectangle.setFillColor(color[tab[i][j]]);
            rectangle.setPosition((i + 0.5) * rectSize.x + affZone.left, (j + 0.5) * rectSize.y + affZone.top);
            window.draw(rectangle);
        }
}

void Board::create(const Vector2u &_size)
{
    size = _size;
    tab = new bool* [size.x];
    for (Uint32 i = 0; i < size.x; i++)
        tab[i] = new bool [size.y];
}

void Board::resize(const Vector2i &back, const Vector2i &front)
{
    bool **newTab;
    Vector2u newSize(size.x + back.x + front.x, size.y + back.y + front.y);

    if (newSize.x < 1 || newSize.y < 1)
        return;
    newTab = new bool* [newSize.x];
    for (Uint32 i = 0; i < newSize.x; i++) {
        newTab[i] = new bool [newSize.y];
        for (Uint32 j = 0; j < newSize.y; j++)
            newTab[i][j] = false;
    }
    for (Uint32 i = max(0, -back.x); i < min(size.x, size.x + front.x); i++)
        for (Uint32 j = max(0, -back.y); j < min(size.y, size.y + front.y); j++)
            newTab[i + back.x][j + back.y] = tab[i][j];
    destroy();
    size = newSize;
    tab = newTab;
}

bool Board::save(const string &fileName) const
{
    try {
        ofstream file(fileName, ifstream::binary | ifstream::trunc);
        vector<Uint8> data;

        if (!file)
            throw ERROR("File " + fileName + " cannot be opened");
        if (!file.write((char*)&size, sizeof(Vector2u)))
            throw ERROR("Write size failed");
        data.resize(size.x * size.y / 8 + (size.x * size.y % 8 ? 1 : 0));
        for (Uint32 i = 0; i < size.x; i++)
            for (Uint32 j = 0; j < size.y; j++)
                data[(i * size.x + j) / 8] |= (tab[i][j] << ((i * size.x + j) % 8));
        if (!file.write((char*)data.data(), sizeof(char) * data.size()))
            throw ERROR("Write data failed");
        if (!file.write((char*)&color, sizeof(Color) * 2))
            throw ERROR("Write color failed");
        const Uint16 swapPatternSize = swapPattern.size();

        if (!file.write((char*)&swapPatternSize, sizeof(Uint16)))
            throw ERROR("Write swapPattern size failed");
        for (Uint16 i = 0; i < swapPattern.size(); i++)
            if (!file.write((char*)&swapPattern[i], sizeof(Vector2i)))
                throw ERROR("Write swapPattern " + to_string(i) + " size failed");
    }
    catch (const exception &e) {
        cerr << "Error : " << e.what() << endl;
        return false;
    }
    return true;
}

bool Board::load(const string &fileName)
{
    try {
        ifstream file(fileName, ifstream::binary);
        vector<Uint8> data;

        if (!file)
            throw ERROR("File " + fileName + " cannot be opened");
        if (!file.read((char*)&size, sizeof(Vector2u)))
            throw ERROR("Read size failed");
        create(size);
        data.resize(size.x * size.y / 8 + (size.x * size.y % 8 ? 1 : 0));
        if (!file.read((char*)data.data(), sizeof(char) * data.size()))
            throw ERROR("Read data failed");
        for (Uint32 i = 0; i < size.x; i++)
            for (Uint32 j = 0; j < size.y; j++)
                tab[i][j] = (data[(i * size.x + j) / 8] & (0b1 << (i * size.x + j) % 8)) ? true : false;
        if (!file.read((char*)&color, sizeof(Color) * 2))
            throw ERROR("Read color failed");
        Uint16 swapPatternSize;

        if (!file.read((char*)&swapPatternSize, sizeof(Uint16)))
            throw ERROR("Read swapPattern size failed");
        swapPattern.resize(swapPatternSize);
        for (Uint16 i = 0; i < swapPattern.size(); i++)
            if (!file.read((char*)&swapPattern[i], sizeof(Vector2i)))
                throw ERROR("Read swapPattern " + to_string(i) + " size failed");
    }
    catch (const exception &e) {
        cerr << "Error : " << e.what() << endl;
        return false;
    }
    return true;
}

void Board::operator=(const Board &other)
{
    create(other.size);
    for (Uint32 i = 0; i < size.x; i++)
        for (Uint32 j = 0; j < size.y; j++)
            tab[i][j] = other.tab[i][j];
    color = other.color;
    swapPattern = other.swapPattern;
}

bool Board::operator==(const Board &other) const
{
    if (size != other.size)
        return false;
    for (Uint32 i = 0; i < size.x; i++)
        for (Uint32 j = 0; j < size.y; j++)
            if (tab[i][j] != other.tab[i][j])
                return false;
    return true;
}

bool Board::operator!=(const Board &other) const
{
    return !operator==(other);
}

void Board::destroy()
{
    for (Uint32 i = 0; i < size.x; i++)
        delete [] tab[i];
    if (size.x > 0)
        delete [] tab;
}
