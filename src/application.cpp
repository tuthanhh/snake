#include "application.h"
#include <iostream>


Application::Application() : currentState(
    new MenuState()
), stateStack() {
    stateStack.push(currentState);
} 

Application::~Application() {
    delete currentState;
    while (!stateStack.empty()) {
        delete stateStack.top();
        stateStack.pop();
    }
}

void Application::run()
{
    using clock = std::chrono::steady_clock;

    timeout(FRAME_DURATION_MS); // Poll input at most once per frame

    auto lastFrame = clock::now();
    long accumulatorMs = 0;

    while (true)
    {
        const auto now = clock::now();
        const auto frameDelta = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastFrame).count();
        lastFrame = now;
        accumulatorMs += frameDelta;

        // Check input safely
        const int ch = getch();
        if (ch != ERR && currentState != nullptr)
        {
            currentState->handleInput(ch);
        }

        // Update loop
        while (accumulatorMs >= FRAME_DURATION_MS && currentState != nullptr && !stateStack.empty())
        {
            currentState->update(FRAME_DURATION_MS);
            accumulatorMs -= FRAME_DURATION_MS;
        }

        // Exit if state stack is empty
        if (currentState == nullptr || stateStack.empty())
        {
            std::cerr << "State stack is empty. Exiting application." << std::endl;
            break;
        }

        // Render safely
        if (currentState != nullptr)
        {
            currentState->render();
        }
    }

    // Clean up ncurses
    endwin();
}
