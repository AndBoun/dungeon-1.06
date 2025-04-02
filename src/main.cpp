//
// Created By Andrew Boun on 4/1/2025
//

#include <random>
#include <sys/time.h>
#include <unistd.h>

#include <dungeon/Dungeon.hpp>
#include <io/SaveLoad.hpp>

int main(int argc, char *argv[])
{
    std::random_device rd;
    unsigned int seed = rd();
    srand(seed); 

    Dungeon d;
    d.generateRandomDungeon();
    d.printDungeon();

    SaveLoad sl;
    sl.load(d);
}