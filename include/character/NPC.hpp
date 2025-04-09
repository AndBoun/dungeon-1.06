//
// Created By Andrew Boun on 4/2/2025
//

#ifndef NPC_HPP
#define NPC_HPP
#include <character/Character.hpp>
#include <string>
#include <vector>
#include <set>
#include <optional>

class NPC : public Character
{
public:
    int intelligent; // 0 or 1
    int telepathy; // 0 or 1
    int tunneling; // 0 or 1
    int erratic; // 0 or 1
    Point pcPosition; // Position of the PC



    


    NPC();
    NPC(Point position, Cell cell, bool isAlive, int ID);
    ~NPC();


    // Getters
    int getIntelligent() const { return intelligent; }
    int getTelepathy() const { return telepathy; }
    int getTunneling() const { return tunneling; }
    int getErratic() const { return erratic; }
    const Point& getPCPostion() const { return pcPosition; }

    // Setters
    void setPCPosition(const Point& position) { pcPosition = position; }
};

#endif