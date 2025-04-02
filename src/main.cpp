//
// Created By Andrew Boun on 4/1/2025
//

#include <random>
#include <sys/time.h>
#include <unistd.h>

#include <dungeon/Dungeon.hpp>

int main(int argc, char *argv[])
{
    std::random_device rd;
    unsigned int seed = rd();
    srand(seed); 

    // struct timeval tv;
    // gettimeofday(&tv, NULL); 
    // srand(tv.tv_usec ^ getpid());

    Dungeon d;
    d.generateRandomDungeon();
    d.printDungeon();

}