//
// Created By Andrew Boun on 4/2/2025
//

#include <io/SaveLoad.hpp>
#include <iostream>

std::string SaveLoad::loadMarker()
{
    char marker[13]; // 12 bytes + 1 for null terminator
    
    // Read exactly 12 bytes
    if (fread(marker, sizeof(char), 12, f) != 12) {
        std::cerr << "Error: Could not read marker from file" << std::endl;
        return "";
    }
    
    // Null terminate the string
    marker[12] = '\0';
    
    return std::string(marker);
}

uint32_t SaveLoad::loadVersion()
{
    uint32_t version;
    
    // Read exactly 4 bytes
    if (fread(&version, sizeof(version), 1, f) != 1) {
        std::cerr << "Error: Could not read version from file" << std::endl;
        return 1;
    }
    
    return be32toh(version);
}

uint32_t SaveLoad::loadSize()
{
    uint32_t size;
    
    // Read exactly 4 bytes
    if (fread(&size, sizeof(size), 1, f) != 1) {
        std::cerr << "Error: Could not read size from file" << std::endl;
        return 1;
    }
    
    return be32toh(size);
}

bool SaveLoad::loadPC(Dungeon &d)
{
    uint8_t pc[2]; // player character
    
    // Read exactly 2 bytes
    if (fread(pc, sizeof(uint8_t), 2, f) != 2) {
        std::cerr << "Error: Could not read pc from file" << std::endl;
        return false;
    }
    // initialize player, set curr_cell to FLOOR temporarily, will be set correctly in load()
    // d->initPlayer(pc[0], pc[1], FLOOR);
    
    return true;
}

bool SaveLoad::loadHardness(Dungeon &d)
{
    std::vector<uint8_t> hardness(1680); // 1680 bytes for hardness
    
    // Read exactly 1680 bytes
    if (fread(hardness.data(), sizeof(uint8_t), 1680, f) != 1680) {
        std::cerr << "Error: Could not read hardness from file" << std::endl;
        return false;
    }
    
    for (int i = 0; i < 1680; i++) {
        Cell cell = d.modifyGrid()[i / DUNGEON_WIDTH][i % DUNGEON_WIDTH];
        cell.setHardness(hardness[i]);
        cell.setType(ROCK);
    }
    
    return true;
}

int SaveLoad::loadNumRooms(Dungeon &d)
{
    uint16_t numRooms;
    
    if (fread(&numRooms, sizeof(uint16_t), 1, f) != 1) {
        std::cerr << "Error: Could not read num_rooms from file" << std::endl;
        return false;
    }
    
    numRooms = be16toh(numRooms);
    numRooms = static_cast<int>(numRooms);
    
    return numRooms;
}
/*
bool SaveLoad::loadRooms(Dungeon& d, int numRooms)
{
    std::vector<uint8_t> rooms(d->numRooms * 4); // 4 bytes per room
    
    if (fread(rooms.data(), sizeof(uint8_t), d->numRooms * 4, file) != d->numRooms * 4) {
        std::cerr << "Error: Could not read rooms from file" << std::endl;
        return false;
    }
    
    for (int i = 0; i < d->numRooms; i++) {
        d->rooms[i].x = static_cast<int>(rooms[i * 4]);
        d->rooms[i].y = static_cast<int>(rooms[i * 4 + 1]);
        d->rooms[i].width = static_cast<int>(rooms[i * 4 + 2]);
        d->rooms[i].height = static_cast<int>(rooms[i * 4 + 3]);
        d->rooms[i].centerX = d->rooms[i].x + d->rooms[i].width / 2;
        d->rooms[i].centerY = d->rooms[i].y + d->rooms[i].height / 2;
        
        d->generateRoom(d->rooms[i]);
    }
    
    return true;
}

bool SaveLoad::loadNumUpStairs(Dungeon* d)
{
    uint16_t numUpStairs;
    
    if (fread(&numUpStairs, sizeof(uint16_t), 1, file) != 1) {
        std::cerr << "Error: Could not read num_up_stairs from file" << std::endl;
        return false;
    }
    
    numUpStairs = be16toh(numUpStairs);
    d->numUpStairs = static_cast<int>(numUpStairs);
    d->upStairs.resize(d->numUpStairs);
    
    return true;
}

bool SaveLoad::loadUpStairs(Dungeon* d)
{
    std::vector<uint8_t> upStairs(d->numUpStairs * 2); // 2 bytes per up_stairs
    
    if (fread(upStairs.data(), sizeof(uint8_t), d->numUpStairs * 2, file) != d->numUpStairs * 2) {
        std::cerr << "Error: Could not read up_stairs from file" << std::endl;
        return false;
    }
    
    for (int i = 0; i < d->numUpStairs; i++) {
        d->grid[upStairs[i * 2 + 1]][upStairs[i * 2]].type = UP_STAIRS;
        d->upStairs[i].x = upStairs[i * 2];
        d->upStairs[i].y = upStairs[i * 2 + 1];
    }
    
    return true;
}

bool SaveLoad::loadNumDownStairs(Dungeon* d)
{
    uint16_t numDownStairs;
    
    if (fread(&numDownStairs, sizeof(uint16_t), 1, file) != 1) {
        std::cerr << "Error: Could not read num_down_stairs from file" << std::endl;
        return false;
    }
    
    numDownStairs = be16toh(numDownStairs);
    d->numDownStairs = static_cast<int>(numDownStairs);
    d->downStairs.resize(d->numDownStairs);
    
    return true;
}

bool SaveLoad::loadDownStairs(Dungeon* d)
{
    std::vector<uint8_t> downStairs(d->numDownStairs * 2); // 2 bytes per down_stairs
    
    if (fread(downStairs.data(), sizeof(uint8_t), d->numDownStairs * 2, file) != d->numDownStairs * 2) {
        std::cerr << "Error: Could not read down_stairs from file" << std::endl;
        return false;
    }
    
    for (int i = 0; i < d->numDownStairs; i++) {
        d->grid[downStairs[i * 2 + 1]][downStairs[i * 2]].type = DOWN_STAIRS;
        d->downStairs[i].x = downStairs[i * 2];
        d->downStairs[i].y = downStairs[i * 2 + 1];
    }
    
    return true;
}

bool SaveLoad::fillInCorridors(Dungeon* d)
{
    for (int i = 0; i < DUNGEON_HEIGHT; i++) {
        for (int j = 0; j < DUNGEON_WIDTH; j++) {
            if (d->grid[i][j].type == ROCK && d->grid[i][j].hardness == 0) {
                d->grid[i][j].type = CORRIDOR;
            }
        }
    }
    
    return true;
}
*/

bool SaveLoad::load(Dungeon &d)
{
    f = fopen(dungeonFile.c_str(), "rb");

    std::cout << "Home: " << home << std::endl;
    std::cout << "Dungeon file: " << dungeonFile << std::endl;
    
    std::string marker = loadMarker();
    std::cout << "Marker: " << marker << std::endl;
    if (marker != EXPECTED_MARKER) {
        std::cerr << "Error: Invalid marker" << std::endl;
        return false;
    }
    
    uint32_t version = loadVersion();
    std::cout << "Version: " << version << std::endl;
    
    uint32_t size = loadSize();
    std::cout << "Size: " << size << std::endl;
    
    if (!loadPC(d)) return false;
    // std::cout << "PC: x: " << d->pc.x << " \t y: " << d->pc.y << std::endl;
    
    if (!loadHardness(d)) return false;
    
    // if (!loadNumRooms(d)) return false;
    int numRooms = loadNumRooms(d);
    std::cout << "Number of rooms: " << numRooms << std::endl;
    /*
    if (!loadRooms(d)) return false;
    
    if (!loadNumUpStairs(d)) return false;
    std::cout << "Number of up stairs: " << d->numUpStairs << std::endl;
    
    if (!loadUpStairs(d)) return false;
    
    if (!loadNumDownStairs(d)) return false;
    std::cout << "Number of down stairs: " << d->numDownStairs << std::endl;
    
    if (!loadDownStairs(d)) return false;
    
    fillInCorridors(d);
    
    // PC has already been initialized, fix the cell type
    d->pc.currCell = d->grid[d->pc.y][d->pc.x].type;
    d->grid[d->pc.y][d->pc.x].type = PLAYER;
    */
    
    fclose(f);
    return true;
}