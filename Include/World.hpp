/*
** EPITECH PROJECT, 2019
** T3x3
** File description:
** World.hpp
*/

#pragma once

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

#define DefaultSwapPartten vector<Vector2i>({{0, 0}, {0, -1}, {0, 1}, {-1, 0}, {1, 0}})

class World // name ?
{
public:
    World(const Uint32 &_size);
    World(const Vector2u &_size);
    World(const string &fileName);
    World(const World &world);
    ~World();
    const Vector2u &getSize() const;
    const bool *const *getTab() const; // ?
    void fill(const bool &state = true);
    void generate(const Uint32 &seed = time(nullptr));
    void randomSwap(const size_t &nbSwap, const Uint32 &seed = time(nullptr));
    void swap(const Vector2u &position);
    void aff(RenderTarget &window, FloatRect affZone = FloatRect(0, 0, 0, 0));
    // TODO bool save(const string &fileName) const; // return bool or throw ?
    bool load(const string &fileName); // return bool or throw ?
    bool operator==(const World &other);

private:
    void create(const Vector2u &_size);


private:
    Vector2u size;
    bool **tab;
    array<Color, 2> color; // use texture ?
    vector<Vector2i> swapPattern;
};
