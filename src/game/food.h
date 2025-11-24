#pragma once
#include "coord.h"
#include <ncurses.h>
struct Food {
    Food();
    explicit Food(const Coord &coord, int value = 1);
    Food(int x, int y, int value = 1);

    void render() const;
    void respawn(const Coord &coord, int value = 1);

    [[nodiscard]] const Coord &position() const noexcept;
    [[nodiscard]] int scoreValue() const noexcept;
    [[nodiscard]] bool isActive() const noexcept;
    void setActive(bool active) noexcept;

private:
    Coord location;
    int value;
    bool active;
};