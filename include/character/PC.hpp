//
// Created By Andrew Boun on 4/2/2025
//

#ifndef PC_HPP
#define PC_HPP
#include <character/Character.hpp>
#include <utils/Point.hpp>
#include <dungeon/base/Cell.hpp>

class PC : public Character
{
public:
    PC();
    PC(Point position, int speed, Cell current_cell, char symbol, bool alive);
    ~PC();
};

#endif