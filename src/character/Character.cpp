//
// Created By Andrew Boun on 4/2/2025
//

#include <character/Character.hpp>
#include <dungeon/base/Cell.hpp>

Character::Character() : position(Point()), speed(0), current_cell(Cell()), symbol(' '), alive(true) {}
Character::Character(Point position, int speed, Cell current_cell, char symbol, bool alive)
    : position(position), speed(speed), current_cell(current_cell), symbol(symbol), alive(alive) {}

Character::~Character() {}

const Point& Character::getPosition() const {
    return position;
}
int Character::getSpeed() const {
    return speed;
}
const Cell& Character::getCurrentCell() const {
    return current_cell;
}
char Character::getSymbol() const {
    return symbol;
}
bool Character::isAlive() const {
    return alive;
}

void Character::setPosition(Point position) {
    this->position = position;
}

void Character::setCurrentCell(Cell current_cell) {
    this->current_cell = current_cell;
}

void Character::setAlive(bool alive) {
    this->alive = alive;
}