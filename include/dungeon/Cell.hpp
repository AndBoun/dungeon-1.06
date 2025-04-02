//
// Created By Andrew Boun on 4/1/2025
//

#ifndef DUNGEON_CELL_HPP
#define DUNGEON_CELL_HPP

class Cell
{
protected:
    int hardness;
    char type;

public:
    Cell();
    Cell(int hardness, char type);
    ~Cell();
    int getHardness() const;
    char getType() const;
    void setHardness(int hardness);
    void setType(char type);
    void setCell(int hardness, char type);
};

#endif
