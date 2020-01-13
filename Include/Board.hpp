/*
** EPITECH PROJECT, 2019
** T3x3
** File description:
** Board.hpp
*/

#pragma once

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

typedef vector<Vector2i> SwapPattern;

#define CrossSwapPartten {{0, -1}, {-1, 0}, {0, 0}, {1, 0}, {0, 1}}
#define SquareSwapPartten {{-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {0, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}}

class Board
{
public:
    Board();
    Board(const Uint32 &_size);
    Board(const Vector2u &_size);
    Board(const string &fileName);
    Board(const Board &board);
    ~Board();
    const Vector2u &getSize() const;
    const bool *const *getTab() const; // ?
    const array<Color, 2> &getColor() const;
    const SwapPattern &getSwapPattern() const;
    void setColor(const array<Color, 2> &_color);
    void setSwapPattern(const SwapPattern &_swapPattern);
    void fill(const bool &state = true);
    void generate(const Uint32 &seed = time(nullptr)); // can generate a fill board !!
    void randomSwap(const size_t &nbSwap, const Uint32 &seed = time(nullptr));
    void swap(const Vector2u &position);
    void aff(RenderTarget &window, FloatRect affZone = FloatRect(0, 0, 0, 0)) const;
    void create(const Vector2u &_size);
    void resize(const Vector2i &back, const Vector2i &front);
    bool save(const string &fileName) const; // return bool or throw ?
    bool load(const string &fileName); // return bool or throw ?
    void operator=(const Board &other);
    bool operator==(const Board &other) const;
    bool operator!=(const Board &other) const;

private:
    Vector2u size;
    bool **tab;
    array<Color, 2> color; // use texture ?
    SwapPattern swapPattern;
};
