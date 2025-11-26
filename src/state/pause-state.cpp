#include "state.h"
#include "application.h"
#include "log/log.h"

void PauseState::handleInput(int ch) {
    switch (ch) {
        case KEY_UP:
            if (selectedOption == Option::QUIT_TO_MENU) {
                selectedOption = Option::RESUME;
            }
            break;
        case KEY_DOWN:
            if (selectedOption == Option::RESUME) {
                selectedOption = Option::QUIT_TO_MENU;
            }
            break;
        case '\n': // Enter key
            if (selectedOption == Option::RESUME) {
                // Pop the pause state to resume the game
                Application::getInstance().popState();
                dynamic_cast<GameState*>(Application::getInstance().currentState)->world.setPaused(false);
            } else if (selectedOption == Option::QUIT_TO_MENU) {
                // Clear the state stack and push the menu state
                Application::getInstance().clearStates();
                Application::getInstance().pushState(new MenuState());
            }
            break;
        default:
            break;
    }
}

void PauseState::update(int dt) {
    // Implement any update logic for the pause state here
    // For example, blinking the selected option
    blinkCounter += dt;
    if (blinkCounter >= 500) { // Toggle every 500 ms
        isBlinkOn = !isBlinkOn;
        blinkCounter = 0;
    }
}

void PauseState::render() {
    clear();
    draw_title();

    int y = 10;
    mvprintw(y++, 10, "Resume");
    mvprintw(y++, 10, "Quit to Menu");

    if (isBlinkOn) {
        switch (selectedOption) {
            case Option::RESUME:
                mvchgat(10, 10, -1, A_REVERSE, 0, nullptr);
                break;
            case Option::QUIT_TO_MENU:
                mvchgat(11, 10, -1, A_REVERSE, 0, nullptr);
                break;
        }
    }

    refresh();
}

void PauseState::draw_title() {
    mvprintw(5, 10, "Paused");
}
