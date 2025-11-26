#include "snake.h"

#include <algorithm>
#include <cmath>

namespace {
constexpr int kDefaultMoveIntervalMs = 150; // ~6.6 moves per second
constexpr int kDefaultInitialLength = 3;
}

Snake::Snake()
    : direction(Direction::RIGHT), pendingDirection(Direction::RIGHT), pendingGrowth(0), moveAccumulatorMs(0),
      moveIntervalMs(kDefaultMoveIntervalMs) {}

void Snake::reset(const Coord &start, int initialLength) {
    body.clear();
    const int length = initialLength > 0 ? initialLength : kDefaultInitialLength;
    for (int i = 0; i < length; ++i) {
        body.push_back(Coord{start.x - i, start.y});
    }
    direction = Direction::RIGHT;
    pendingDirection = Direction::RIGHT;
    pendingGrowth = 0;
    moveAccumulatorMs = 0;
    moveIntervalMs = kDefaultMoveIntervalMs;
}

void Snake::handleInput(int ch) {
    switch (ch) {
        case KEY_UP:
            if (direction != Direction::DOWN) {
                pendingDirection = Direction::UP;
            }
            break;
        case KEY_DOWN:
            if (direction != Direction::UP) {
                pendingDirection = Direction::DOWN;
            }
            break;
        case KEY_LEFT:
            if (direction != Direction::RIGHT) {
                pendingDirection = Direction::LEFT;
            }
            break;
        case KEY_RIGHT:
            if (direction != Direction::LEFT) {
                pendingDirection = Direction::RIGHT;
            }
            break;
        default:
            break;
    }
}

void Snake::update(int dt) {
    moveAccumulatorMs += dt;
}

void Snake::render() const {
    int height, width;
    getmaxyx(stdscr, height, width);

    const double cellHeight = static_cast<double>(height) / WORLD_HEIGHT;
    const double cellWidth = static_cast<double>(width) / WORLD_WIDTH;

    for (const auto &segment : body) {
        const int xStart = static_cast<int>(std::floor(segment.x * cellWidth));
        const int xEnd = std::min(width, std::max(xStart + 1, static_cast<int>(std::ceil((segment.x + 1) * cellWidth))));
        const int yStart = static_cast<int>(std::floor(segment.y * cellHeight));
        const int yEnd = std::min(height, std::max(yStart + 1, static_cast<int>(std::ceil((segment.y + 1) * cellHeight))));

        for (int y = yStart; y < yEnd; ++y) {
            for (int x = xStart; x < xEnd; ++x) {
                mvaddch(y, x, '#');
            }
        }
    }

}

void Snake::setDirection(Direction dir) {
    direction = dir;
}

Snake::Direction Snake::getDirection() const noexcept {
    return direction;
}

const Coord &Snake::head() const noexcept {
    static Coord dummy;
    return body.empty() ? dummy : body.front();
}

const Snake::Body &Snake::segments() const noexcept {
    return body;
}

void Snake::grow(int amount) {
    pendingGrowth += amount;
}

bool Snake::occupies(const Coord &point) const {
    for (const auto& segment : body) {
        if (segment == point) {
            return true;
        }
    }
    return false;
}

void Snake::advance() {
    if (body.empty()) {
        return;
    } else {
        Coord newHead = nextHeadPosition();
        body.push_front(newHead);
        if (pendingGrowth > 0) {
            --pendingGrowth;
        } else {
            body.pop_back();
        }
    }
}

Coord Snake::nextHeadPosition() const {
    Coord head = body.empty() ? Coord{0,0} : body.front();
    switch(direction) {
        case Direction::UP:
            head.y -= 1;
            break;
        case Direction::DOWN:
            head.y += 1;
            break;
        case Direction::LEFT:
            head.x -= 1;
            break;
        case Direction::RIGHT:
            head.x += 1;
            break;
    }
    return head;
}

bool Snake::consumeMoveStep() {
    if (body.empty() || moveAccumulatorMs < moveIntervalMs) {
        return false;
    }

    moveAccumulatorMs -= moveIntervalMs;
    direction = pendingDirection;
    return true;
}
