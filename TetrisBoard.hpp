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
    struct riga {
        string name;
        int score;
        riga* next;
    };
    int yMax, xMax;
    int yDim, xDim;
    int compl_lines;
    int level;
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
    // REVIEW order of functions
    // movements:
    int tetraFall(int &fall_rate) ;
    void checkCompletedLines(int &fall_rate);

    int incr_score(int, int );

    void moveLeft() ;

    void moveRight();

    void pigliaTetramino();

    int fallCompletely(int &fall_rate);

public:

    TetrisBoard() ;

    int getInput(int inpt, int &fall_rate) ;

    // utilities
    void printColors(WINDOW* thisWin, short colorNumber, const char* s);

    void reload();

    void deleteWin(WINDOW* window);

    void remove();
};

#endif
