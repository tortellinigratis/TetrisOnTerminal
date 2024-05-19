#include "Menu.hpp"
#include "TetrisBoard.hpp"
#include "Leaderboard.hpp"
#include "ncrss.cpp"

using namespace std;

int showMenu(Menu* mMenu) {
    int n = -1;
    while ( n == -1 ) {
        n = mMenu-> getInput();
    }
    return n;
}

int playTetris(TetrisBoard* tBoard) {
    int n = 0;
    while ( n == 0 ) {
        n = tBoard-> getInput();
    }
    return n;
}

int showLeaderboard(Leaderboard* lBoard) {
    int n = 1;
    while ( n == 1 ) {
        n = lBoard-> getInput();
    }
    return n;
}

int main() {
    initscr();
    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_YELLOW, COLOR_YELLOW); 
        init_pair(2, COLOR_CYAN, COLOR_CYAN); 
        init_pair(3, COLOR_BLUE, COLOR_BLUE); 
        init_pair(4, COLOR_WHITE, COLOR_WHITE); 
        init_pair(5, COLOR_GREEN, COLOR_GREEN); 
        init_pair(6, COLOR_MAGENTA, COLOR_MAGENTA); 
        init_pair(7, COLOR_RED, COLOR_RED);
        init_pair(11, COLOR_GREEN, COLOR_BLACK);
        init_pair(12, COLOR_CYAN, COLOR_BLACK);
        init_pair(13, COLOR_YELLOW, COLOR_BLACK);
    } else {
        printw("No colors were found, errors may occur.");
    }
    refresh();

    noecho();
    keypad(stdscr, true);
    curs_set(0);

    Menu mainMenu = Menu();
    TetrisBoard tBoard = TetrisBoard();
    Leaderboard lBoard = Leaderboard();

    bool inApp = true;
    // NOTE inpt cases: -1, menu
    //                   0, game
    //                   1, leaderboard
    //                   2, exit
    int inpt = -1;
    while ( inApp ) {
        switch ( inpt ) {
            case -1:
                // remove eventual loaded windows;
                tBoard.remove();
                // load the menu;
                mainMenu.reload();
                inpt = showMenu(&mainMenu);
                break;
            case 0:
                // start the game;
                mainMenu.remove();
                tBoard.reload();
                inpt = playTetris(&tBoard);
                break;
            case 1:
                // show the leaderboard;
                mainMenu.remove();
                lBoard.reload();
                inpt = showLeaderboard(&lBoard);
                break;
            case 2:
                // exit the app;
                mainMenu.remove();
                inApp = false;
                break;
            default:
                // REVIEW some error handling;
                break;
        }
    }

    endwin();
    return 0;
}