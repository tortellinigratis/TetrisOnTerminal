//#include <ncurses.h>
#include <ncurses/ncurses.h>
#include "Menu.h"
#include "TetrisBoard.h"
#include "Leaderboard.h"

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