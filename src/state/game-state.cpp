#include "state.h"
#include "application.h"
void GameState::handleInput(int ch) {
    switch (ch) {
    case 27: // ESC key
        world.setPaused(true);
        Application::getInstance().pushState(new PauseState());
        break;
    default:
        world.handleInput(ch);
        break; 
    }
    return; 
}
void GameState::update(int dt) {
    world.update(dt);
}
void GameState::render() {
    clear();
    world.render();
    refresh();
}