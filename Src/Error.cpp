/*
** EPITECH PROJECT, 2019
** T3x3
** File description:
** Error.cpp
*/

#include "Error.hpp"

using namespace std;

Error::Error(const string &_message, const string &_file, const string &_function, const size_t &_line)
    : message(_message), file(_file), function(_function), line(_line)
{
    str = message + " (file:" + file + " | function:" + function + " | line:" + to_string(line) + ")";
}

const char *Error::what() const throw()
{
    return str.c_str();
}
