//
// Created By Andrew Boun on 4/2/2025
//

#include <character/PC.hpp>

PC::PC() : Character() {}
PC::PC(Point position, int speed, Cell current_cell, char symbol, bool alive)
    : Character(position, speed, current_cell, symbol, alive) {}
PC::~PC() {}
