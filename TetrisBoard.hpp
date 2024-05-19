#ifndef TETRISBOARD_HPP
#define TETRISBOARD_HPP

#include <string.h>
#include <fstream>
#include <iostream>
#include "tetramino.hpp"
#include "time.h"
#include "ncrss.cpp"
#include <vector>

#define XLENGTH 10
#define YLENGTH 20
// List of possible blocks to choose from
#define POSS_TETRAM 7
#define maxc 15 //max carattere nome
using namespace std;

class TetrisBoard {
private:
    int yMax, xMax;
    int yDim, xDim;
    WINDOW* win;
    WINDOW* winNext;
    WINDOW* winHold;
    short boardArray[YLENGTH][XLENGTH];
    bool can_hold;
    Tetramino* ttrmn;
    Tetramino* ttrmnNext;
    int typeHold;
    int score;
    string highscore;

    WINDOW* score_win;
    WINDOW* name_win;
    WINDOW* nome;

    
    int yPosition, xPosition;

    void init() ;
    bool is_empty(istream&);

    bool is_empty_f(fstream& );
    
    void randomTtrmn() ;
    void clearboard() ;

    void showBoard() ;

    void drawTetramino() ;

    void drawHold();

    void drawNext();

    int addBlock() ;
    void name_player();
    bool clearUnder() ;

    bool clearLeft() ;

    bool clearRight() ;

    bool clearRotation() ;
    // movements:
    int tetraFall() ;
    void checkCompletedLines();

    int incr_score(int );

    void moveLeft() ;

    void moveRight();

    void pigliaTetramino();

    int fallCompletely() ;

public:

    TetrisBoard() ;
    const int fallDelay = 1000;
    clock_t lastFall = clock();

    int getInput() ;

// utilities
    // REVIEW probably useless
    /*int incr_score (int n)
    {
        return 0;
    }
    WINDOW* getWinPointer() {
        return this-> win;
    }*/

    int count_digit(int );

    // REVIEW check if these functions are actually used and how
    void render();

    void reload();

    void remove();
};

#endif
