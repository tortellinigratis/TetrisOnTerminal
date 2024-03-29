#include <ncurses.h>
#include <string.h>
#include "tetramino.h"
#include "time.h"

#define XLENGTH 20
#define YLENGTH 22
// List of possible blocks to choose from
#define POSS_TETRAM 2

class TetrisBoard {
private:
    int yMax, xMax;
    int yDim, xDim;
    WINDOW* win;
    bool boardArray[YLENGTH][XLENGTH];
    Tetramino* ttrmn;

    int yPosition, xPosition;

    void init() {
        yPosition = 0;
        randomTtrmn();
        xPosition = (xDim /2) - (ttrmn-> getMaxDim() /2) -1;
        this-> win = newwin(yDim, xDim, (yMax /2) - (yDim /2), (xMax /2) - (xDim /2));
        wborder(this-> win, 0, 0, ' ', 0, ' ', ' ', 0, 0);
        mvwprintw(this-> win, 1, 0, " ");
        mvwprintw(this-> win, 2, 0, " ");
        mvwprintw(this-> win, 1, xDim -1, " ");
        mvwprintw(this-> win, 2, xDim -1, " ");
        clearboard();
        showBoard();
        drawTetramino();
        refresh();
        wrefresh(this-> win);
    }

    void randomTtrmn() {
        srand(time(NULL));
        int rndm = rand() % POSS_TETRAM;
        switch ( rndm ) {
            case 0:
                ttrmn = new Square();
                break;
            case 1:
                ttrmn = new Rect();
                break;
            default:
                ttrmn = new Square();
                break;
        }
    }

    void clearboard() {
        for ( int i = 0; i < YLENGTH; i++ ) {
            for ( int j = 0; j < XLENGTH; j++ ) {
                boardArray[i][j] = false;
            }
        }
    }

    void showBoard() {
        for ( int i = 0; i < YLENGTH; i++ ) {
            wmove(this-> win, i +1, 1);
            for ( int j = 0; j < XLENGTH; j++ ) {
                if ( boardArray[i][j] ) {
                    wprintw(this-> win, "#");
                } else {
                    wprintw(this-> win, " ");
                }
            }
        }
        wrefresh(this-> win);
        refresh();
    }

    void drawTetramino() {
        for ( int i = 0; i < 4; i++ ) {
            wmove(this-> win, yPosition +i +1, xPosition+1);
            for ( int j = 0; j < 4; j++ ) {
                if ( ttrmn-> isTrue(i, j) ) {
                    wprintw(this-> win, "#");
                } else {
                    wmove(this-> win, yPosition +i +1, xPosition +j +2);
                }
            }
        }
        wrefresh(this-> win);
        refresh();
    }

    int addBlock() {
        for ( int i = 0; i < ttrmn-> getMaxDim(); i++ ) {
            for ( int j = 0; j < ttrmn-> getMaxDim(); j++ ) {
                if ( ttrmn-> isTrue(i, j) ) {
                    boardArray[i + yPosition][j + xPosition] = true;
                }
            }
        }
        delete ttrmn;
        // check if the game has ended
        for ( int i = 0; i < 2; i++ ) {
            for ( int j = 0; j < XLENGTH; j++ ) {
                if ( boardArray[i][j] ) {
                    // TODO open "write your name" for leaderboard puposes
                    return -1;
                }
            }
        }

        // extract a new Tetramino
        randomTtrmn();
        yPosition = 0;
        xPosition = (xDim /2) - (ttrmn-> getMaxDim() /2) -1;
        return 0;
    }

    bool clearUnder() {
        for ( int i = 0; i < ttrmn-> getMaxDim(); i++ ) {
            for ( int j = 0; j < ttrmn-> getMaxDim(); j++ ) {
                if ( ttrmn-> isTrue(i, j) ) {
                    if ( yPosition +i +1 == YLENGTH || boardArray[yPosition +i +1][xPosition + j] ) {
						// TODO potential improvement, for-loop could be stopped at the first true bottom element of each column
                        return false;
                    }
                }
            }
        }
        return true;
    }

    bool clearLeft() {
        for ( int i = 0; i < ttrmn-> getMaxDim(); i++ ) {
            for ( int j = 0; j < ttrmn-> getMaxDim(); j++ ) {
                if ( ttrmn-> isTrue(i, j) ) {
                    if ( xPosition +j == 0 || boardArray[yPosition +i][xPosition + j -1] ) {
                        // TODO potential improvement, for-loop could be stopped at the first true left element of each row
                        return false;
                    }
                }
            }
        }
        return true;
    }

    bool clearRight() {
        for ( int i = 0; i < ttrmn-> getMaxDim(); i++ ) {
            for ( int j = 0; j < ttrmn-> getMaxDim(); j++ ) {
                if ( ttrmn-> isTrue(i, j) ) {
                    if ( xPosition +j +1 == XLENGTH || boardArray[yPosition +i][xPosition + j +1] ) {
						// TODO potential improvement, for-loop could be stopped at the first true right element of each row
                        return false;
                    }
                }
            }
        }
        return true;
    }

    bool clearRotation() {
        for ( int i = 0; i < ttrmn-> getMaxDim(); i++ ) {
            for ( int j = 0; j < ttrmn-> getMaxDim(); j++ ) {
                if ( boardArray[i+yPosition][j+xPosition] && ttrmn-> isTrue(i, j) ) {
                    return false;
                }
            }
        }
        return true;
    }

    // movements:
    int tetraFall() {
        if ( clearUnder() ) {
            yPosition++;
            return 0;
        } else {
            return addBlock();
        }
    }

    void moveLeft() {
        if ( clearLeft() ) {
            xPosition--;
        }
    }

    void moveRight() {
        if ( clearRight() ) {
            xPosition++;
        }
    }

    int fallCompletely() {
        int r = 0;
        bool moving = true;
        while ( moving ) {
            r = tetraFall();
            if ( yPosition == 0 ) {
                moving = false;
            }
        }
        return r;
    }

public:

    TetrisBoard() {
        getmaxyx(stdscr, this-> yMax, this-> xMax);
        if ( this-> yMax < this-> yDim ) {
            // REVIEW error handling: not enough vertical space
        } else if ( this-> xMax < this-> xDim ) {
            // REVIEW error handling: not enough horizontal space;
        }
        xDim = XLENGTH +2;
        yDim = YLENGTH +2;
        this-> win = NULL;
    }

    int getInput() {
        timeout(1000);
        int r = 0;
        switch( getch() ) {
			// REVIEW each case should have all 3 possible type of key (see backspace for reference)
            case KEY_RIGHT:
                moveRight();
                break;

            case KEY_LEFT:
                moveLeft();
                break;

            case ' ':
                r = fallCompletely();
                break;

            case 'r':
                ttrmn-> rotate();
                if ( !clearRotation() ) {
                    ttrmn-> antiRotate();
                }
                break;

			case 'q':
				ttrmn-> antiRotate();
                if ( !clearRotation() ) {
                    ttrmn-> rotate();
                }
				break;

            // esc cases: Slower but more intuitive
            case 27:
            // backspace cases: faster, less intuitive but still effective
            case KEY_BACKSPACE:
            case 127:
            case '\b':
                return -1;

            default:
                r = tetraFall();
                break;
        }
        if ( r == -1 ) {
            return r;
        } else {
            showBoard();
            drawTetramino();
            return r;
        }
    }

// utilities
    // REVIEW probably useless
    WINDOW* getWinPointer() {
        return this-> win;
    }

    // REVIEW check if these functions are actually used and how
    void render() {
        if ( this-> win != NULL ) {
            refresh();
            wrefresh(this-> win);
        } else {
            init();
        }
    }

    void reload() {
        if ( this-> win != NULL ) {
            remove();
        }
        init();
    }

    void remove() {
        if ( this-> win != NULL ) {
            wclear(this-> win);
            wrefresh(this-> win);
            delwin(this-> win);
            this-> win = NULL;
            refresh();
        }
    }
};