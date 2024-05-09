#include <string.h>
#include "tetramino.h"
#include "time.h"
#include "ncrss.cpp"

#define XLENGTH 10
#define YLENGTH 20
// List of possible blocks to choose from
#define POSS_TETRAM 2
#define maxc 15 //max carattere nome
using namespace std;

class TetrisBoard {
private:
    int yMax, xMax;
    int yDim, xDim;
    WINDOW* win;
    WINDOW* winNext;
    bool boardArray[YLENGTH][XLENGTH];
    Tetramino* ttrmn;
    Tetramino* ttrmnNext;
    int score;

    WINDOW* score_win;



    int yPosition, xPosition;

    void init() {
        score = 0;
        yPosition = 0;
        randomTtrmn();
        ttrmn = ttrmnNext;
        randomTtrmn();
        xPosition = (xDim /2) - (ttrmn-> getMaxDim() /2) -1;
        this-> win = newwin(yDim, xDim, (yMax /2) - (yDim /2), (xMax /2) - (xDim /2));
        this->score_win = newwin(6, 17, (yMax /2) - (yDim /2) + 3, (xMax /2) - (xDim /2)+ 20);
        box(this->score_win, 0, 0); 
        mvwprintw(this->score_win, 1, 1, "Top ");
        //highscore da mettere che si muove col punteggio
        ifstream readscore;
        readscore.open("scores.txt");
        string a = "0";
        const char *u;
        if(!is_empty(readscore)){
            readscore.ignore(maxc, readscore.widen('\n'));
            getline(readscore,a);	
        }
        u = a.c_str();
        wattron(score_win, A_REVERSE);
		mvwprintw(score_win, 2, 1, u);
        wattroff(score_win, A_REVERSE);
        mvwprintw(this->score_win, 3, 1, "Score ");
        a = to_string(score);
        u = a.c_str();
        wattron(score_win, A_REVERSE);
        mvwprintw(this->score_win, 4, 1, u); 
        wattroff(score_win, A_REVERSE);
        wborder(this-> win, 0, 0, ' ', 0, ' ', ' ', 0, 0);
        mvwprintw(this-> win, 1, 0, " ");
        mvwprintw(this-> win, 2, 0, " ");
        mvwprintw(this-> win, 1, xDim -1, " ");
        mvwprintw(this-> win, 2, xDim -1, " ");
        clearboard();
        showBoard();

        winNext = newwin (8, 8, (yMax /2) - (yDim /2)+10, (xMax /2) - (xDim /2)+30);
        box(winNext, 0, 0);
        mvwprintw(winNext, 0, 1 , " Next ");

        drawNext();
        drawTetramino();
        refresh();
        wrefresh(this-> win);
        wrefresh(this-> score_win);
    }

    bool is_empty(ifstream& file){
		return file.peek() == ifstream :: traits_type :: eof();
	}
    
    void randomTtrmn() {
        srand(time(NULL));
        int rndm = rand() % POSS_TETRAM;
        switch ( rndm ) {
            case 0:
                ttrmnNext = new Square();
                // ttrmn = new Square();
                break;
            case 1:
                ttrmnNext = new Rect();
                //ttrmn = new Rect();
                break;
            default:
                ttrmnNext = new Square();
                //ttrmn = new Square();
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
                    wprintw(this-> win, "@");
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
                    wprintw(this-> win, "@");
                } else {
                    wmove(this-> win, yPosition +i +1, xPosition +j +2);
                }
            }
        }
        wrefresh(this-> win);
        refresh();
    }

    void drawNext(){
        wmove(winNext, 2,2);
        for ( int i = 0; i < 4; i++ ) {
            for ( int j = 0; j < 4; j++ ) {
                if ( ttrmnNext-> isTrue(i, j) ) {
                    wprintw(this-> winNext, "@");
                } else {
                    wprintw(this-> winNext, " ");
                }
            }
            wmove(winNext, 2+i+1, 2);
        }
        wrefresh(this-> winNext);
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
        // NOTE: yPosition is here and not where randomTtrmn() is called (couple of lines beneath) because if the game ends and I
        //       called addBlock() from fallCompletely(), the exit condition ( yPosition == 0 ) is never true, therefore tetraFall()
        //       is called and tries to use ttrmn, which does no longer exists.
        yPosition = 0;
        delete ttrmn;
        ttrmn = NULL;
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
        ttrmn = ttrmnNext;
        randomTtrmn();
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
                // controls: esiste gia' un blocco in quel posto                                                    uscirebbe dal basso         uscirebbe a destra          uscirebbe a sinistra
                if ( ( boardArray[i+yPosition][j+xPosition] && ttrmn-> isTrue(i, j) ) || ( ttrmn-> isTrue(i, j) && (i + yPosition >= YLENGTH || j + xPosition >= XLENGTH || xPosition < 0 ) ) ) {
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
            int r = addBlock();
            checkCompletedLines();
            return r;
        }

    }

    void checkCompletedLines(){    
        int cont = 0;
        for(int y=0; y<YLENGTH; y++)
        {
            bool isLineCleared = true;
            for(int x=0; x< XLENGTH && isLineCleared ; x++)
            {
                if(boardArray[y][x] == false)
                {
                    isLineCleared = false; //se trovo un "buco" esco dal for e sono sicuro di aver trovato una riga non completa
                } 
            }
            if(isLineCleared)
            {
                if(y==0)
                {
                    for(int x=0; x< XLENGTH ; x++)
                    {
                        boardArray[0][x]=false;
                    }
                }
                else
                {
                    for(int y2=y; y2>0; y2--)
                    {
            
                        for(int x2=0; x2< XLENGTH ; x2++)
                        {
                            boardArray[y2][x2]=boardArray[y2-1][x2];
                        }
                    }
                }
                cont++;
                
            }
            
        }
        score = incr_score(cont);
        string a;
        const char *u;
        a = to_string(score);
        u = a.c_str();
        wattron(score_win, A_REVERSE);
        mvwprintw(this->score_win, 4, 1, u); 
        wattroff(score_win, A_REVERSE);
        wrefresh(score_win);
    }

    int incr_score(int n){
        switch(n){
            case 0:
                break;
            case 1:
                score = score + 40;
                break;
            case 2:
                score = score + 100;
                break;
            case 3:
                score = score + 300;
                break;
            case 4:
                score = score + 1200;
                break;
        }
        return score;
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
        this->score_win = NULL;
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
       if ( r != -1 ) {
            showBoard();
            drawTetramino();
            drawNext();
        }
        return r;
    }

// utilities
    // REVIEW probably useless
    /*int incr_score (int n)
    {
        return 0;
    }
    WINDOW* getWinPointer() {
        return this-> win;
    }*/

    int count_digit(int number)
    {
        int count = 0;
        while(number!=0){
            number = number / 10;
            count++;
        }
        return count;
    }

    // REVIEW check if these functions are actually used and how
    void render() {
        if ( this-> win != NULL ) {
            refresh();
            wrefresh(this-> win);
            wrefresh(this->score_win);
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
            wclear(winNext);
            wrefresh(winNext);
            delwin(winNext);
            winNext=NULL;
            wclear(this-> win);
            wclear(this->score_win);
            wrefresh(this->score_win);
            wrefresh(this-> win);
            wclear(this->score_win);
            delwin(this-> win);
            delwin(this->score_win);
            this->score_win = NULL;
            this-> win = NULL;
            delete ttrmn;
            this-> ttrmn = NULL;
            delete ttrmnNext;
            this-> ttrmnNext = NULL;
            refresh();
        }
    }
};
