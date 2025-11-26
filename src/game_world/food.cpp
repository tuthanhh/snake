#include "food.h"
#include <algorithm>
#include <cmath>

Food::Food() : location(0, 0), value(0), active(false) {}

Food::Food(const Coord &coord, int pointValue) : location(coord), value(pointValue), active(true) {}

Food::Food(int x, int y, int pointValue) : Food(Coord{x, y}, pointValue) {}

void Food::render() const {
    int height, width;
    getmaxyx(stdscr, height, width);
    const double cellHeight = static_cast<double>(height) / WORLD_HEIGHT;
    const double cellWidth = static_cast<double>(width) / WORLD_WIDTH;

    const int xStart = static_cast<int>(std::floor(location.x * cellWidth));
    const int xEnd = std::min(width, std::max(xStart + 1, static_cast<int>(std::ceil((location.x + 1) * cellWidth))));
    const int yStart = static_cast<int>(std::floor(location.y * cellHeight));
    const int yEnd = std::min(height, std::max(yStart + 1, static_cast<int>(std::ceil((location.y + 1) * cellHeight))));

    for (int y = yStart; y < yEnd; ++y) {
        for (int x = xStart; x < xEnd; ++x) {
            mvaddch(y, x, '*');
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
