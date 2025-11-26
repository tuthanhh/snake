#pragma once
#include "coord.h"
#include <deque>
#include <vector>
#include <ncurses.h>

struct Snake {
    enum class Direction {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    using Body = std::deque<Coord>;

    Snake();

    void reset(const Coord &start, int initialLength = 2);
    void handleInput(int ch);
    void update(int dt);
    void render() const;

    bool consumeMoveStep();

    void setDirection(Direction dir);
    Direction getDirection() const noexcept;

    const Coord &head() const noexcept;
    const Body &segments() const noexcept;

    void grow(int amount = 1);
    bool occupies(const Coord &point) const;

    Coord nextHeadPosition() const;
    void advance();

private:
    Body body;
    Direction direction;
    Direction pendingDirection;
    int pendingGrowth;
    int moveAccumulatorMs;
    int moveIntervalMs;
};