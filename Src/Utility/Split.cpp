/*
** EPITECH PROJECT, 2019
** for_norme
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
