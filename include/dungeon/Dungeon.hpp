//
// Created By Andrew Boun on 4/1/2025
//

#ifndef DUNGEON_HPP
#define DUNGEON_HPP

#include <array>
#include <vector>
#include <memory>

#include <dungeon/Cell.hpp>
#include <dungeon/Room.hpp>
#include <dungeon/Stair.hpp>
#include <utils/Point.hpp>


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

    // PC pc;
    // NPC npc

    // std::vector<NPC> npcs;

public:
    Dungeon();
    ~Dungeon();

    void generateRandomDungeon();

    bool generateRandomRoom();
    bool placeRoom(Room &room);

    bool placeStair(int x, int y, char stairType);
    bool generateRandomStair(char stairType);
    
    void printDungeon() const;


private:
    void initializeCells();

    bool canInsertRoom(Room &room);
    bool generateRooms();

    void generateStairs();

    void generateCorridors();
    
};

#endif