/*
** EPITECH PROJECT, 2019
** T3x3
** File description:
** SoundBox.hpp
*/

#pragma once

#include <regex> // ?
#include <SFML/Audio.hpp>
#include "Utility/Globpp.hpp"
#include "Utility/Split.hpp"

using namespace std;
using namespace sf;

class SoundBox
{
public:
    static const SoundBox &getInstance();
    Sound getSound(const string &soundName) const;

private:
    SoundBox(const string &soundDirectory = "Resources/Sound");
    ~SoundBox() = default;
    SoundBox &operator=(const SoundBox &soundBox) = delete;

private:
    static SoundBox instance;
    map<string, SoundBuffer> soundBufferMap;
};
