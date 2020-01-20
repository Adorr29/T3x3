/*
** EPITECH PROJECT, 2019
** T3x3
** File description:
** Globpp.cpp
*/

#include <glob.h>
#include "Utility/Globpp.hpp"
#include "Error.hpp"

vector<string> globpp(const string &pattern, const bool &recursive)
{
    vector<string> pathList;
    glob_t pglob;

    if (glob(pattern.c_str(), GLOB_MARK, NULL, &pglob))
        throw ERROR("glob error");
    for (size_t i = 0; i < pglob.gl_pathc; i++) {
        const string path(pglob.gl_pathv[i]);

        if (recursive && path.back() == '/') {
            const vector<string> pathList2 = globpp(path + "*", true);

            pathList.insert(pathList.end(), pathList2.begin(), pathList2.end());
        }
        else
            pathList.push_back(path);
    }
    globfree(&pglob);
    return pathList;
}
