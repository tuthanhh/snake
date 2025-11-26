#pragma once
constexpr int WORLD_WIDTH = 32;
constexpr int WORLD_HEIGHT = 18;

struct Coord {
    int x;
    int y;

    Coord() : x(0), y(0) {}
    Coord(int xCoord, int yCoord) : x(xCoord), y(yCoord) {}

    bool operator==(const Coord &other) const noexcept { return x == other.x && y == other.y; }
    bool operator!=(const Coord &other) const noexcept { return !(*this == other); }
    bool operator<(const Coord &other) const noexcept {
        return (y < other.y) || (y == other.y && x < other.x);
    }
};