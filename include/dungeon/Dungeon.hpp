//
// Created By Andrew Boun on 4/1/2025
//

#ifndef DUNGEON_HPP
#define DUNGEON_HPP

#include <array>
#include <vector>
#include <memory>

#include <dungeon/base/Cell.hpp>
#include <dungeon/base/Room.hpp>
#include <dungeon/base/Stair.hpp>

#include <character/Character.hpp>
#include <character/PC.hpp>
#include <character/NPC.hpp>

#include <utils/Point.hpp>

const char DEFAULT_NUM_MONSTERS = 10;

const char ROCK = ' '; // Rock
const char FLOOR = '.'; // Floor
const char UP_STAIR = '<'; // Up stair
const char DOWN_STAIR = '>'; // Down stair
const char CORRIDOR = '#'; // Corridor
const char PLAYER = '@'; // Player

const int DUNGEON_WIDTH = 80; // Width of the dungeon
const int DUNGEON_HEIGHT = 21; // Height of the dungeon
const int PLACABLE_WIDTH = 78; // Width of the playable area
const int PLACABLE_HEIGHT = 19; // Height of the playable area

const int MAX_HARDNESS = 255; // Maximum hardness of a cell
const int MIN_HARDNESS = 0; // Minimum hardness of a cell

const int MAX_ROOMS = 120; // Maximum number of randomly generated rooms
const int MIN_ROOMS = 6; // Minimum number of randomly generated rooms
const int MIN_ROOM_WIDTH = 4; // Minimum width of a room
const int MIN_ROOM_HEIGHT = 3; // Minimum height of a room

const int MIN_DOWN_STAIRS = 1;
const int MAX_DOWN_STAIRS = 4;
const int MIN_UP_STAIRS = 1;
const int MAX_UP_STAIRS = 4;

const int MAX_ATTEMPTS = 2000; // Maximum attempts to place a room

class Dungeon
{
protected:
    std::array<std::array<Cell, DUNGEON_WIDTH>, DUNGEON_HEIGHT> grid;

    std::vector<Room> rooms;
    std::vector<Stair> up_stairs;
    std::vector<Stair> down_stairs;

    PC pc;
    // NPC npc

    // std::vector<NPC> npcs;

public:
    Dungeon();
    ~Dungeon();

    // Get Arrays
    const std::array<std::array<Cell, DUNGEON_WIDTH>, DUNGEON_HEIGHT>& getGrid() { return grid; }
    const std::vector<Room>& getRooms () { return rooms; }
    const std::vector<Stair>& getUpStairs () { return up_stairs; }
    const std::vector<Stair>& getDownStairs () { return down_stairs; }

    PC& getPC() { return pc; }

    // Modify Arrays
    std::array<std::array<Cell, DUNGEON_WIDTH>, DUNGEON_HEIGHT>& modifyGrid() { return grid; }
    std::vector<Room>& modifyRooms () { return rooms; }
    std::vector<Stair>& modifyStairs () { return up_stairs; }
    std::vector<Stair>& modifyDownStairs () { return down_stairs; }


    void generateRandomDungeon(int numNPCs = DEFAULT_NUM_MONSTERS);

    bool generateRandomRoom();
    bool placeRoom(Room &room);

    bool placeStair(int x, int y, char stairType);
    bool generateRandomStair(char stairType);

    bool placeCharacterRandomly(Character &character);
    bool placeCharacter(Character &character, int x, int y);
    
    void printDungeon() const;


private:
    void initializeCells();

    bool canInsertRoom(Room &room);
    bool generateRooms();

    void generateStairs();

    void generateCorridors();
    
};

#endif