#ifndef TETRISBOARD_HPP
#define TETRISBOARD_HPP

#include <string.h>
#include <fstream>
#include <iostream>
#include "tetramino.hpp"
#include "platform.hpp"
#include <ctime>

#define XLENGTH 10
#define YLENGTH 20
// List of possible blocks to choose from
#define POSS_TETRAM 8
#define maxc 15 //max carattere nome
#define INITIAL_RATE 1000 //valore iniziale in millisecondi che definisce l'intervallo di discesa del tetramino
#define MIN_RATE 25 //valore più basso in millisecondi raggiungibile da fall_rate
#define REF_LEV 5 //livello fino al quale viene sottratto FIRST_RATE
#define FIRST_RATE 75 //valore sottratto in millisecondi a fall_rate per i primi REF_LEV livelli
#define SECOND_RATE 25 //valore sottratto in millisecondi a fall_rate da quando si raggiunge REF_LEV a quando fall_rate è maggiore di MIN_RATE

using namespace std;

class TetrisBoard {
private:
    struct riga { // struttra utilizzata per salvare momentaneamente tutti gli score della leaderboard
        string name;
        int score;
        riga* next;
    };

    // main board variables
    int yMax, xMax;
    int yDim, xDim;
    int yPosition, xPosition;
    short boardArray[YLENGTH][XLENGTH];
    Tetramino* ttrmn;
    WINDOW* win;

    // score and level screens
    int fall_rate;
    int compl_lines;
    int level;
    WINDOW* lev_win;
    string highscore;
    int score;
    WINDOW* score_win;

    // next tetramino screen
    Tetramino* ttrmnNext;
    WINDOW* winNext;

    // hold tetramino screen
    int typeHold;
    bool can_hold;
    WINDOW* winHold;
    WINDOW* tetris;

    // endgame screen (to save the score)
    WINDOW* name_win;
    WINDOW* nome;

    // some useful functions
    void init();
    void printColors(WINDOW* thisWin, short colorNumber, const char* s);
    void clearboard();
    void showBoard();
    void drawTetramino();
    void randomTtrmn();
    void pigliaTetramino();
    
    void drawHold();

    void drawNext();

    // lines and points
    int addBlock();
    void checkCompletedLines();
    int incr_score(int, int);

    // endgame functions
    void name_player();
    bool is_empty(istream&);

    // movements:
    int tetraFall() ;
    bool clearUnder();
    bool clearLeft();
    bool clearRight();
    bool clearRotation();
    void moveLeft() ;
    void moveRight();
    int fallCompletely();

public:
    TetrisBoard();
    int getInput(int inpt);
    int getFallRate();

    // the usual
    void reload();

    void deleteWin(WINDOW* window);

    void remove();
};

#endif
