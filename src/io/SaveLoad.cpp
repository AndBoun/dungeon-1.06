//
// Created By Andrew Boun on 4/1/2025
//

#include <io/SaveLoad.hpp>
#include <iostream>

SaveLoad::SaveLoad()
{
    home = getenv("HOME");
    dungeonFile = home + "/.rlg327/dungeon";
    dungeonFileLength = dungeonFile.length();
}

SaveLoad::~SaveLoad()
{
    if (f) {
        fclose(f);
    }
}