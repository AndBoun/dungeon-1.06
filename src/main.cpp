//
// Created By Andrew Boun on 4/1/2025
//

#include <random>
#include <sys/time.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

#include <dungeon/Dungeon.hpp>
#include <io/SaveLoad.hpp>
#include <pathfinding/Dijkstras.hpp>
#include <ui/ui.hpp>

int main(int argc, char *argv[])
{
    std::random_device rd;
    unsigned int seed = rd();
    srand(seed); 

    Dungeon d;
    SaveLoad sl;

    int load_flag = 0;
    int save_flag = 0;
    int num_monsters = DEFAULT_NUM_MONSTERS;

    // Parse command line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--load") == 0) {
            load_flag = 1;
            if (i + 1 >= argc) continue; 
            if (argv[i + 1][0] == '-' && argv[i + 1][1] == '-') continue;
            sl = SaveLoad(argv[++i]);
        } else if (strcmp(argv[i], "--save") == 0) {
            save_flag = 1;
        } else if (strcmp(argv[i], "--nummon") == 0) {
            num_monsters = atoi(argv[++i]);
        }
    }

    if (load_flag) {
        sl.load(d);
    } else {
        d.generateRandomDungeon();
    }

    if (save_flag) {
        sl = SaveLoad();
        sl.save(d);
    }

    ui::init_ncurses();

    while (d.startGameplay(num_monsters) == - 2){
        d.resetDungeon();
    }

    ui::destroy_ncurses();

    // d.printDungeon();
}