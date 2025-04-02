//
// Created By Andrew Boun on 4/1/2025
//

#include <dungeon/Dungeon.hpp>
#include <iostream>

Dungeon::Dungeon() {}
Dungeon::~Dungeon() {}

void Dungeon::generateRandomDungeon()
{
    do {
        initializeCells(); // Initialize the cells with rock
        if (!generateRooms()) continue; // Generate rooms, reset if failed
        generateCorridors();
        generateStairs();
        break;
    } while (true);
}

void Dungeon::initializeCells()
{
    for (int y = 0; y < DUNGEON_HEIGHT; y++) {
        for (int x = 0; x < DUNGEON_WIDTH; x++) {
            if (y == 0 || y == DUNGEON_HEIGHT - 1 || x == 0 || x == DUNGEON_WIDTH - 1){
                grid[y][x].setCell(MAX_HARDNESS, ROCK);
            }
            else {
                int curr_hardness = rand() % (MAX_HARDNESS - 1 - MIN_HARDNESS) + 1;
                grid[y][x].setCell(curr_hardness, ROCK);
            }
        }
    }
}
