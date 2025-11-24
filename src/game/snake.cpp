#include "snake.h"

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
    int box_y = height/WORLD_HEIGHT; 
    int box_x = width/WORLD_WIDTH;
    for (const auto& segment : body) {
        int draw_x = segment.x * box_x;
        int draw_y = segment.y * box_y;
        for (int y = 0; y < box_y; ++y) {
            for (int x = 0; x < box_x; ++x) {
                mvaddch(draw_y + y, draw_x + x, '#');
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
