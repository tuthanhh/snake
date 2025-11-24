#include "world.h"

#include <iostream>
#include <vector>

World::World(int width, int height)
    : boardWidth(width), boardHeight(height), scoreValue(0), gameOver(false) {
    reset();
}

void World::reset() {
    scoreValue = 0;
    gameOver = false;
    snake = Snake{};
    snake.reset(Coord{boardWidth / 2, boardHeight / 2});
    foodItems.clear();
    spawnFood();
}

void World::handleInput(int ch) {
    if (!gameOver) {
        switch (ch) {
            case KEY_UP:
            case KEY_DOWN:
            case KEY_LEFT:
            case KEY_RIGHT:
                snake.handleInput(ch);
                break;
            default:
                break;
        }
    }
}

void World::update(int dt) {
    if (!gameOver) {
        snake.update(dt);
        while (snake.consumeMoveStep()) {
            advance();
        }
    }
    
}

void World::render() const {
    drawBound();
    snake.render();
    for (const auto& [coord, food] : foodItems) {
        if (food.isActive()) {
            food.render();
        }
    }
}
void World::drawBound() const { 
    int height, width;
    getmaxyx(stdscr, height, width);
    int box_y = height / boardHeight; 
    int box_x = width / boardWidth;

    // Draw top borders
    for (int x = 0; x < width; ++x) {
        mvaddch(0, x, '#');
    }
    // Draw bottom borders
    for (int x = 0; x < width; ++x) {
        mvaddch(box_y * boardHeight - 1, x, '#');
    }
    // Draw left borders
    for (int y = 0; y < height; ++y) {
        mvaddch(y, 0, '#');
    }
    // Draw right borders
    for (int y = 0; y < height; ++y) {
        mvaddch(y, box_x * boardWidth - 1, '#');
    }
}

int World::score() const noexcept {
    return scoreValue;
}

bool World::isGameOver() const noexcept {
    return gameOver;
}

const Snake &World::getSnake() const noexcept {
    return snake;
}

const std::map<Coord, Food> &World::getFood() const noexcept {
    return foodItems;
}

void World::advance() {
    Coord nextHead = snake.nextHeadPosition();

    if (detectWallCollision(nextHead) || detectSelfCollision(nextHead)) {
        gameOver = true;
        return;
    }

    if (consumeFood(nextHead)) {
        snake.grow();
        scoreValue += 10;
        spawnFood();
    }
    snake.advance();
}

void World::spawnFood() {
    // Simple spawning logic: find a random unoccupied position
    static std::mt19937 rng(std::random_device{}());
    std::vector<Coord> freePositions;

    for (int x = 0; x < boardWidth; ++x) {
        for (int y = 0; y < boardHeight; ++y) {
            Coord potentialPos{x, y};
            if (!isCellOccupied(potentialPos)) {
                freePositions.push_back(potentialPos);
            }
        }
    }

    if (!freePositions.empty()) {
        std::uniform_int_distribution<std::size_t> dist(0, freePositions.size() - 1);
        Coord spawnPos = freePositions[dist(rng)];
        foodItems[spawnPos] = Food(spawnPos, 1);
    }
}

bool World::consumeFood(const Coord &nextHead) {
    auto it = foodItems.find(nextHead);
    if (it != foodItems.end() && it->second.isActive()) {
        it->second.setActive(false);
        return true;
    }
    return false;
}

bool World::detectSelfCollision(const Coord &nextHead) const {
    for (const auto& segment : snake.segments()) {
        if (segment == nextHead) {
            return true;
        }
    }
    return false;
}

bool World::detectWallCollision(const Coord &nextHead) const {
    return !isInsideBounds(nextHead);
}

bool World::isInsideBounds(const Coord &point) const noexcept {
    return point.x >= 0 && point.x < boardWidth && point.y >= 0 && point.y < boardHeight;
}

bool World::isCellOccupied(const Coord &point) const {
    if (snake.occupies(point)) {
        return true;
    }

    auto foodIt = foodItems.find(point);
    return foodIt != foodItems.end() && foodIt->second.isActive();
}