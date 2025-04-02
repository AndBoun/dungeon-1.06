//
// Created By Andrew Boun on 4/1/2025
//

#include <dungeon/Dungeon.hpp>
#include <iostream>

Dungeon::Dungeon() {}
Dungeon::~Dungeon() {}

void Dungeon::generateRandomDungeon(int numNPCS)
{
    do {
        initializeCells(); // Initialize the cells with rock
        if (!generateRooms()) continue; // Generate rooms, reset if failed
        generateCorridors();
        generateStairs();
        placeCharacterRandomly(pc); // Place the player character randomly
        placeNPCsRandomly(numNPCS); // Place NPCs randomly
        break;
    } while (true);
}

bool Dungeon::placeNPCsRandomly(int numNPCS)
{
    for (int i = 0; i < numNPCS; i++) {
        NPC npc = NPC(Point(), Cell(), true, i);
        if (placeCharacterRandomly(npc)) {
            npcs.push_back(npc);
        }
    }
    return true;
}

