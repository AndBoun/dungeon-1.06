//
// Created By Andrew Boun on 4/1/2025
//

#include <dungeon/Room.hpp>
#include <utils/Point.hpp>
#include <iostream>

Room::Room() : Point(), width(0), height(0), topLeft(nullptr), center(nullptr) {}

Room::Room(int x, int y, int width, int height) : Point(x, y), width(width), height(height) {
    topLeft = new Point(x, y);
    center = new Point(x + width / 2, y + height / 2);
}
Room::~Room() {
    delete topLeft;
    delete center;
}
int Room::getWidth() const { return width; }
int Room::getHeight() const { return height; }
void Room::setWidth(int width) { this->width = width; }
void Room::setHeight(int height) { this->height = height; }

void Room::setTopLeft(int x, int y) {
    if (topLeft) {
        topLeft->setPoint(x, y);
    } else {
        topLeft = new Point(x, y);
    }
    this->center->setPoint(x + width / 2, y + height / 2);
}