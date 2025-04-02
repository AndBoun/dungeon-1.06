//
// Created By Andrew Boun on 4/1/2025
//

#include <dungeon/Dungeon.hpp>
#include <iostream>

void Dungeon::printDungeon() const
{
    // Print top border
    std::cout << std::string(DUNGEON_WIDTH + 2, '-') << std::endl;

    // Print dungeon content with side borders
    for (int y = 0; y < DUNGEON_HEIGHT; y++) {
        std::cout << "|"; // Left border
        for (int x = 0; x < DUNGEON_WIDTH; x++) {
            char cellChar = grid[y][x].getType();
            std::cout << cellChar;
        }
        std::cout << "|" << std::endl; // Right border
    }
    
    // Print bottom border
    std::cout << std::string(DUNGEON_WIDTH + 2, '-') << std::endl;
}