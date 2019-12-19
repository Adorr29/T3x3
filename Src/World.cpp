/*
** EPITECH PROJECT, 2019
** T3x3
** File description:
** World.cpp
*/

#include "World.hpp"
#include "Error.hpp"

World::World(const Uint32 &_size)
    : World(Vector2u(_size, _size))
{
}

World::World(const Vector2u &_size)
    : color({Color(50, 50, 50), Color(250, 160, 0)}),
      swapPattern(DefaultSwapPartten)
{
    create(_size);
}

World::World(const string &fileName)
{
    if (!load(fileName))
        throw ERROR("load failed");
}

World::World(const World &world)
    : World(Vector2u(world.size.x, world.size.y))
{
    for (size_t i = 0; i < size.x; i++)
        for (size_t j = 0; j < size.y; j++)
            tab[i][j] = world.tab[i][j];
    color = world.color;
    swapPattern = world.swapPattern;
}

World::~World()
{
    for (size_t i = 0; i < size.x; i++)
        delete [] tab[i];
    delete [] tab;
}

const Vector2u &World::getSize() const
{
    return size;
}

const bool *const *World::getTab() const
{
    return tab;
}

void World::fill(const bool &state)
{
    for (size_t i = 0; i < size.x; i++)
        for (size_t j = 0; j < size.y; j++)
            tab[i][j] = state;
}

void World::generate(const Uint32 &seed)
{
    fill();
    srand(seed);
    for (size_t i = 0; i < size.x; i++)
        for (size_t j = 0; j < size.y; j++)
            if (rand() % 2)
                swap(Vector2u(i, j));
}

void World::randomSwap(const size_t &nbSwap, const Uint32 &seed)
{
    vector<Vector2u> caseList(size.x * size.y);

    srand(seed);
    for (size_t i = 0; i < size.x; i++)
        for (size_t j = 0; j < size.y; j++)
            caseList[i] = Vector2u(i, j);
    for (size_t i = 0; i < nbSwap && i < caseList.size(); i++) {
        const size_t index = rand() % caseList.size();

        swap(caseList[index]);
        caseList.erase(caseList.begin() + index);
    }
}

void World::swap(const Vector2u &position)
{
    for (const Vector2i &one : swapPattern) {
        const Vector2u toSwap(position.x + one.x, position.y + one.y);

        if (toSwap.x < size.x && toSwap.y < size.y)
            tab[toSwap.x][toSwap.y] = !tab[toSwap.x][toSwap.y];
    }
}

void World::aff(RenderTarget &window, FloatRect affZone)
{
    if (affZone == FloatRect(0, 0, 0, 0))
        affZone = FloatRect(Vector2f(0, 0), Vector2f(window.getSize()));
    const Vector2f rectSize(affZone.width / size.x, affZone.height / size.y);
    RectangleShape rectangle;

    rectangle.setSize(rectSize * (float)0.97);
    rectangle.setOrigin(rectangle.getSize() / (float)2);
    for (size_t i = 0; i < size.x; i++)
        for (size_t j = 0; j < size.y; j++) {
            rectangle.setFillColor(color[tab[i][j]]);
            rectangle.setPosition((i + 0.5) * rectSize.x, (j + 0.5) * rectSize.y);
            window.draw(rectangle);
        }
}

bool World::load(const string &fileName)
{
    // TODO
    return true;
}

void World::create(const Vector2u &_size)
{
    size = _size;
    tab = new bool* [size.x];
    for (size_t i = 0; i < size.x; i++)
        tab[i] = new bool [size.y];
}

bool World::operator==(const World &other)
{
    if (size != other.size)
        return false;
    for (size_t i = 0; i < size.x; i++)
        for (size_t j = 0; j < size.y; j++)
            if (tab[i][j] != other.tab[i][j])
                return false;
    return true;
}
