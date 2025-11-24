#pragma once
// Define different types of states in the application
#include <ncurses.h>
#include "game/world.h"

struct State {
    enum class Type {
        NONE,
        MENU,
        GAME,
        PAUSE,
        GAMEOVER
    };
    State(): type(Type::NONE) {}
    State(Type type) : type(type) {}
    virtual ~State() = default;

    virtual void handleInput(int ch) = 0; // Pure virtual function for handling input
    virtual void update(int dt) = 0; // Pure virtual function for updating state
    virtual void render() = 0; // Pure virtual function for rendering state
    Type type;
};

struct MenuState : public State {
    enum class Option {
        START_GAME,
        EXIT
    };
    Option selectedOption;
    bool isBlinkOn = true;
    int blinkCounter = 0;

    MenuState() : State(Type::MENU), selectedOption(Option::START_GAME) {}

    void handleInput(int ch) override;
    void update(int dt) override; 
    void render() override;
    void draw_title(); 
};

struct GameState : public State {
    GameState() : State(Type::GAME), world() {}
    World world; 

    void handleInput(int ch) override;
    void update(int dt) override; 
    void render() override;
};