#include "state.h"
#include <string.h>
#include <iostream>
#include "application.h"

void MenuState::handleInput(int ch) {
    switch (ch) {
        case KEY_UP:
            if (selectedOption == Option::EXIT) {
                selectedOption = Option::START_GAME;
            }
            break;
        case KEY_DOWN:
            if (selectedOption == Option::START_GAME) {
                selectedOption = Option::EXIT;
            }
            break;
        case '\n': // Enter key
            if (selectedOption == Option::START_GAME) {
                // Transition to game state logic
                Application::getInstance().pushState(new GameState());
            } else if (selectedOption == Option::EXIT) {
                Application::getInstance().clearStates();
            }
            break;
        default:
            break;
    }
}
void MenuState::update(int dt) {
    blinkCounter += dt;
    if (blinkCounter >= 500) { // Toggle every 500 ms
        isBlinkOn = !isBlinkOn;
        blinkCounter = 0;
    }
}


void MenuState::render() {
    clear();
    draw_title();

    int height, width;
    getmaxyx(stdscr, height, width);

    if (selectedOption == Option::START_GAME && isBlinkOn) {
        attron(A_REVERSE);
    }

    mvprintw(height / 3 * 2, (width - strlen("Start")) / 2, "Start");
    if (selectedOption == Option::START_GAME && isBlinkOn) {
        attroff(A_REVERSE);
    }

    if (selectedOption == Option::EXIT && isBlinkOn) {
        attron(A_REVERSE);
    }
    mvprintw(height / 3 * 2 + 2, (width - strlen("Exit")) / 2, "Exit");
    if (selectedOption == Option::EXIT && isBlinkOn) {
        attroff(A_REVERSE);
    }

    refresh();
}


void MenuState::draw_title() {
    static const char *title[] = {
"          _____                    _____                    _____                    _____                    _____          ",
"         /\\    \\                  /\\    \\                  /\\    \\                  /\\    \\                  /\\    \\         ",
"        /::\\    \\                /::\\____\\                /::\\    \\                /::\\____\\                /::\\    \\        ",
"       /::::\\    \\              /::::|   |               /::::\\    \\              /:::/    /               /::::\\    \\       ",
"      /::::::\\    \\            /:::::|   |              /::::::\\    \\            /:::/    /               /::::::\\    \\      ",
"     /:::/\\:::\\    \\          /::::::|   |             /:::/\\:::\\    \\          /:::/    /               /:::/\\:::\\    \\     ",
"    /:::/__\\:::\\    \\        /:::/|::|   |            /:::/__\\:::\\    \\        /:::/____/               /:::/__\\:::\\    \\    ",
"    \\:::\\   \\:::\\    \\      /:::/ |::|   |           /::::\\   \\:::\\    \\      /::::\\    \\              /::::\\   \\:::\\    \\   ",
"  ___\\:::\\   \\:::\\    \\    /:::/  |::|   | _____    /::::::\\   \\:::\\    \\    /::::::\\____\\________    /::::::\\   \\:::\\    \\  ",
" /\\   \\:::\\   \\:::\\    \\  /:::/   |::|   |/\\    \\  /:::/\\:::\\   \\:::\\    \\  /:::/\\:::::::::::\\    \\  /:::/\\:::\\   \\:::\\    \\ ",
"/::\\   \\:::\\   \\:::\\____\\/:: /    |::|   /::\\____\\/:::/  \\:::\\   \\:::\\____\\/:::/  |:::::::::::\\____\\/:::/__\\:::\\   \\:::\\____\\",
"\\:::\\   \\:::\\   \\::/    /\\::/    /|::|  /:::/    /\\::/    \\:::\\  /:::/    /\\::/   |::|~~~|~~~~~     \\:::\\   \\:::\\   \\::/    /",
" \\:::\\   \\:::\\   \\/____/  \\/____/ |::| /:::/    /  \\/____/ \\:::\\/:::/    /  \\/____|::|   |           \\:::\\   \\:::\\   \\/____/ ",
"  \\:::\\   \\:::\\    \\              |::|/:::/    /            \\::::::/    /         |::|   |            \\:::\\   \\:::\\    \\     ",
"   \\:::\\   \\:::\\____\\             |::::::/    /              \\::::/    /          |::|   |             \\:::\\   \\:::\\____\\    ",
"    \\:::\\  /:::/    /             |:::::/    /               /:::/    /           |::|   |              \\:::\\   \\::/    /    ",
"     \\:::\\/:::/    /              |::::/    /               /:::/    /            |::|   |               \\:::\\   \\/____/     ",
"      \\::::::/    /               /:::/    /               /:::/    /             |::|   |                \\:::\\    \\         ",
"       \\::::/    /               /:::/    /               /:::/    /              \\::|   |                 \\:::\\____\\        ",
"        \\::/    /                \\::/    /                \\::/    /                \\:|   |                  \\::/    /        ",
"         \\/____/                  \\/____/                  \\/____/                  \\|___|                   \\/____/         ",
                                                                                                                             
    };
   

    int height, width;
    getmaxyx(stdscr, height, width);

    int lines = sizeof(title) / sizeof(title[0]);

    // Vertical start position (1/3 from top)
    int start_y = height / 3 - lines / 2;

    // Print each line centered horizontally
  
    for (int i = 0; i < lines; i++)
    {
        int x = (width - strlen(title[i])) / 2;
        mvprintw(start_y + i, x, "%s", title[i]);
    }

}
