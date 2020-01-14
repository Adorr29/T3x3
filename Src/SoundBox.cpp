/*
** EPITECH PROJECT, 2019
** T3x3
** File description:
** SoundBox.cpp
*/

#include <iostream> // tmp
#include "SoundBox.hpp"
#include "Error.hpp"

SoundBox SoundBox::instance;

const SoundBox &SoundBox::getInstance()
{
    return instance;
}

Sound SoundBox::getSound(const string &soundName) const
{
    auto it = soundBufferMap.find(soundName);

    if (it == soundBufferMap.end())
        throw ERROR("Sound \"" + soundName + "\" doesn't excite");
    return Sound(it->second);
}

SoundBox::SoundBox(const string &soundDirectory)
{
    const vector<string> fileNameList = globpp(soundDirectory + "/*");
    SoundBuffer soundBuffer;

    for (const string &fileName : fileNameList)
        if (soundBuffer.loadFromFile(fileName)) {
            string soundName = fileName.substr(fileName.rfind('/') + 1);

            soundName = soundName.substr(0, soundName.rfind('.'));
            soundBufferMap[soundName] = soundBuffer;
        }
}
