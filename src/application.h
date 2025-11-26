#pragma once
#include "state.h"
#include <memory>
#include <stack>
#include <ncurses.h>
#include <chrono>

#define FRAME_DURATION_MS 16 // Approximate duration for ~60 FPS
class Application {
public:
    // Implementing singleton pattern for Application
    static Application& getInstance() {
        static Application instance;
        return instance;
    }

    State* currentState;
    std::stack<State*> stateStack;

    void run();
    void pushState(State* state) {
        stateStack.push(state);
        currentState = state;
    }
    void clearStates() {
        while (!stateStack.empty()) {
            State* topState = stateStack.top();
            stateStack.pop();
            delete topState;
        }
        currentState = nullptr;
    }
    void popState()
    {
        if (!stateStack.empty())
        {
            State *topState = stateStack.top(); // get the object pointer
            stateStack.pop();                   // remove it from the stack
            delete topState;                    // safely delete it

            // Update currentState
            currentState = stateStack.empty() ? nullptr : stateStack.top();
        }
    }

    private: 
    Application();
    ~Application();

};