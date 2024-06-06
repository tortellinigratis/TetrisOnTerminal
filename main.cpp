#include "Menu.hpp"
#include "TetrisBoard.hpp"
#include "Leaderboard.hpp"
#include "platform.hpp"
#include <chrono>

using namespace std;

int showMenu(Menu* mMenu) {
    int n = -1;
    while ( n == -1 ) {
        n = mMenu-> getInput();
    }
    return n;
}

int playTetris(TetrisBoard* tBoard, int &fall_rate) {
    int n = 0;
    int r = fall_rate;
    char inpt;
    chrono::time_point<std::chrono::high_resolution_clock> t_start, t_end;
    // time diff
    while ( n == 0 ) {
        t_start = chrono::high_resolution_clock::now();
        timeout(r);
        n = tBoard-> getInput(getch(), fall_rate);
        t_end = chrono::high_resolution_clock::now();
        r += (int)std::chrono::duration_cast<chrono::milliseconds>(t_start - t_end).count();
        
        if ( r <= 0 ) {
            r = fall_rate;
        }
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
        init_pair(14, COLOR_RED, COLOR_BLACK);
        init_pair(15, COLOR_BLUE, COLOR_BLACK);
        init_pair(16, COLOR_MAGENTA, COLOR_BLACK);
    } else {
        printw("No colors were found, errors may occur. ");
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
    int fall_rate = 1000;
    int inpt = -1;
    while ( inApp ) {
        switch ( inpt ) {
            case -1:
                // remove eventual loaded windows;
                tBoard.remove();
                lBoard.remove();
                // load the menu;
                mainMenu.reload();
                inpt = showMenu(&mainMenu);
                break;
            case 0:
                mainMenu.remove();
                lBoard.remove();
                // start the game;
                tBoard.reload();
                inpt = playTetris(&tBoard, fall_rate);
                break;
            case 1:
                mainMenu.remove();
                tBoard.remove();
                // show the leaderboard;
                lBoard.reload();
                inpt = showLeaderboard(&lBoard);
                break;
            case 2:
                // exit the app;
                mainMenu.remove();
                inApp = false;
                break;
            default:
                printw("Somehow you managed to get here... interesting... ^C to exit and try again. ");
                break;
        }
    }

    endwin();
    return 0;
}