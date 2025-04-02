//
// Created By Andrew Boun on 4/2/2025
//

#include <character/NPC.hpp>
#include <math.h>

NPC::~NPC() {}

NPC::NPC() : Character(Point(), 0, Cell(), '!', false, 0) {}

NPC::NPC(Point position, Cell cell, bool isAlive, int ID){
    intelligent = rand() % 2, telepathy = rand() % 2;
    tunneling = rand() % 2, erratic = rand() % 2;

    // m->intelligent = 1, m->telepathy = 0;
    // m->tunneling = 0, m->erratic = 0;

    speed = (rand() % 16) + 5;

    this->position = position;

    pcPosition = Point(-1, -1); // PC position is unknown

    int traits = 
        intelligent +
        (telepathy << 1) +
        (tunneling << 2) +
        (erratic << 3);

    if (traits < 10) {
        symbol = '0' + traits; // 0-9
    } else {
        symbol = 'A' + (traits - 10); // A-F
    }


    this->alive = isAlive;
    this->ID = ID;
    this->currentCell = cell;
}