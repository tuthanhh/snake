#pragma once
#include "coord.h"
#include "snake.h"
#include "food.h"
#include <ncurses.h>
#include <map>
#include <random>


struct World {
    explicit World(int width = WORLD_WIDTH, int height = WORLD_HEIGHT);

    void reset();
    void handleInput(int ch);
    void update(int dt);
    void render() const;
    void setPaused(bool paused) noexcept { isPaused = paused; }

    [[nodiscard]] int score() const noexcept;
    [[nodiscard]] bool isGameOver() const noexcept;

    bool isPaused = false;

    const Snake &getSnake() const noexcept;
    const std::map<Coord, Food> &getFood() const noexcept;

private:
    void advance();
    void spawnFood();
    bool consumeFood(const Coord &nextHead);
    bool detectSelfCollision(const Coord &nextHead) const;
    bool detectWallCollision(const Coord &nextHead) const;
    [[nodiscard]] bool isInsideBounds(const Coord &point) const noexcept;
    [[nodiscard]] bool isCellOccupied(const Coord &point) const;
    void drawBound() const;
    void drawHorizontalLine(int y, int width) const;
    void drawVerticalLine(int x, int height) const;

    int boardWidth;
    int boardHeight;
    int scoreValue;
    bool gameOver;

    Snake snake;
    std::map<Coord, Food> foodItems;
}; 