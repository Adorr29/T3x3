/*
** EPITECH PROJECT, 2019
** T3x3
** File description:
** Split.cpp
*/

#include <sstream>
#include "Utility/Split.hpp"

vector<string> split(const string &str, const char &delim)
{
    vector<string> elemList;
    stringstream stream(str);
    string elem;

    while (getline(stream, elem, delim))
        elemList.push_back(elem);
    return elemList;
}
