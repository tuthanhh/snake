#include "food.h"

Food::Food() : location(0, 0), value(0), active(false) {}

Food::Food(const Coord &coord, int pointValue) : location(coord), value(pointValue), active(true) {}

Food::Food(int x, int y, int pointValue) : Food(Coord{x, y}, pointValue) {}

void Food::render() const {
    int height, width;
    getmaxyx(stdscr, height, width);
    int box_y = height/WORLD_HEIGHT; 
    int box_x = width/WORLD_WIDTH;
    int draw_x = location.x * box_x;
    int draw_y = location.y * box_y;
    for (int y = 0; y < box_y; ++y) {
        for (int x = 0; x < box_x; ++x) {
            mvaddch(draw_y + y, draw_x + x, '*');
        }
    }
}

void Food::respawn(const Coord &coord, int pointValue) {
    location = coord;
    value = pointValue;
    active = true;
}

const Coord &Food::position() const noexcept {
    return location;
}

int Food::scoreValue() const noexcept {
    return value;
}

bool Food::isActive() const noexcept {
    return active;
}

void Food::setActive(bool isActive) noexcept {
    active = isActive;
}
