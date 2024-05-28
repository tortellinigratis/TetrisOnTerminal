#ifndef TETRISBOARD_HPP
#define TETRISBOARD_HPP

#include <string.h>
#include <fstream>
#include <iostream>
#include "tetramino.hpp"
#include "ncrss.cpp"
#include <vector>
#include <ctime>

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
    WINDOW* tetris;
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

    int getInput(int inpt) ;

    // utilities
    void printColors(WINDOW* thisWin, short colorNumber);

    void reload();

    void deleteWin(WINDOW* window);

    void remove();
};

#endif
