#include <cstdlib>
#include <ncurses.h>
#include <csignal>
#include "application.h"    

int main()
{
    // 1. Tell ncurses where to find the definition for "xterm-256color"
    // specific to Arch/Linux systems.
    setenv("TERMINFO", "/usr/share/terminfo", 1);

    Application& appInstance = Application::getInstance();

    initscr();            /* Start curses mode 		*/

    cbreak();             /* Line buffering disabled, Pass on
                           * everty thing to me 		*/

    intrflush(stdscr, FALSE);
    keypad(stdscr, TRUE); /* We get F1, F2 etc..		*/
    curs_set(0);          /* Hide the cursor          */
    noecho();             /* Don't echo() while we do getch */

    std::signal(SIGINT, [](int){ endwin(); std::exit(0); });
    appInstance.run();    

    endwin();  /* End curses mode		  */

    return 0;
}