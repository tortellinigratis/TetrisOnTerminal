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
    int compl_lines;
    int level;
    int *fall_rate;
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
    WINDOW* lev_win;

    int yPosition, xPosition;

    void init(int &fall_rate) ;
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
    int tetraFall(int &fall_rate) ;
    void checkCompletedLines(int &fall_rate);
//REVIEW - un paio di &fall_rate passati non servono
    int incr_score(int, int );

    void moveLeft() ;

    void moveRight();

    void pigliaTetramino();

    int fallCompletely(int &fall_rate) ;

public:

    TetrisBoard() ;

    int getInput(int inpt, int &fall_rate) ;

    // utilities
    void printColors(WINDOW* thisWin, short colorNumber);

    void reload(int &fall_rate);

    void deleteWin(WINDOW* window);

    void remove();
};

#endif
