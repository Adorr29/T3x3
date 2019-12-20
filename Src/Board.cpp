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

Board::Board(const Uint32 &_size)
    : Board(Vector2u(_size, _size))
{
}

Board::Board(const Vector2u &_size)
    : color({Color(50, 50, 50), Color(250, 160, 0)}),
      swapPattern(CrossSwapPartten)
{
    create(_size);
}

Board::Board(const string &fileName)
{
    if (!load(fileName))
        throw ERROR("Load failed");
}

Board::Board(const Board &board)
    : Board(Vector2u(board.size.x, board.size.y))
{
    for (Uint32 i = 0; i < size.x; i++)
        for (Uint32 j = 0; j < size.y; j++)
            tab[i][j] = board.tab[i][j];
    color = board.color;
    swapPattern = board.swapPattern;
}

Board::~Board()
{
    for (Uint32 i = 0; i < size.x; i++)
        delete [] tab[i];
    delete [] tab;
}

const Vector2u &Board::getSize() const
{
    return size;
}

const bool *const *Board::getTab() const
{
    return tab;
}

void Board::setSwapPattern(const vector<Vector2i> &_swapPattern)
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
    fill();
    srand(seed);
    for (Uint32 i = 0; i < size.x; i++)
        for (Uint32 j = 0; j < size.y; j++)
            if (rand() % 2)
                swap(Vector2u(i, j));
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

void Board::swap(const Vector2u &position)
{
    for (const Vector2i &one : swapPattern) {
        const Vector2u toSwap(position.x + one.x, position.y + one.y);

        if (toSwap.x < size.x && toSwap.y < size.y)
            tab[toSwap.x][toSwap.y] = !tab[toSwap.x][toSwap.y];
    }
}

void Board::aff(RenderTarget &window, FloatRect affZone)
{
    if (affZone == FloatRect(0, 0, 0, 0))
        affZone = FloatRect(Vector2f(0, 0), Vector2f(window.getSize()));
    const Vector2f rectSize(affZone.width / size.x, affZone.height / size.y);
    RectangleShape rectangle;

    rectangle.setSize(rectSize * (float)0.97);
    rectangle.setOrigin(rectangle.getSize() / (float)2);
    for (Uint32 i = 0; i < size.x; i++)
        for (Uint32 j = 0; j < size.y; j++) {
            rectangle.setFillColor(color[tab[i][j]]);
            rectangle.setPosition((i + 0.5) * rectSize.x, (j + 0.5) * rectSize.y);
            window.draw(rectangle);
        }
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
        cerr << "size : " << size.x << " " << size.y << endl;
        create(size);
        data.resize(size.x * size.y / 8 + (size.x * size.y % 8 ? 1 : 0));
        if (!file.read((char*)data.data(), sizeof(char) * data.size()))
            throw ERROR("Read data failed");
        for (Uint32 i = 0; i < size.x; i++)
            for (Uint32 j = 0; j < size.y; j++) {
                cerr << "X : " << (data[(i * size.x + j) / 8] & (0b1 << (i * size.x + j) % 8)) << endl;
                tab[i][j] = (data[(i * size.x + j) / 8] & (0b1 << (i * size.x + j) % 8)) ? true : false;
                cerr << "tab[" << i << "][" << j << "] : " << (tab[i][j] ? "true" : "false") << endl;
            }
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

void Board::create(const Vector2u &_size)
{
    size = _size;
    tab = new bool* [size.x];
    for (Uint32 i = 0; i < size.x; i++)
        tab[i] = new bool [size.y];
}

bool Board::operator==(const Board &other)
{
    if (size != other.size)
        return false;
    for (Uint32 i = 0; i < size.x; i++)
        for (Uint32 j = 0; j < size.y; j++)
            if (tab[i][j] != other.tab[i][j])
                return false;
    return true;
}
