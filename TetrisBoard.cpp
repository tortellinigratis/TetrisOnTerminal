#include "TetrisBoard.hpp"

    void TetrisBoard::init() {
        fall_rate = 1000;
        compl_lines = 0;
        level = 0;
        score = 0;
        can_hold = true;
        yPosition = 0;
        randomTtrmn();
        typeHold = -1; 
        ttrmn = ttrmnNext;
        randomTtrmn();
        xPosition = (xDim /2) - (ttrmn-> getMaxDim() /2) -1;
        this->lev_win = newwin(6, 17, (yMax /2) - (yDim /2) + 3, (xMax /2) - (xDim /2) - 25);
        this-> win = newwin(yDim, xDim + 10 , (yMax /2) - (yDim /2), (xMax /2) - (xDim /2) - 5);
        this->score_win = newwin(6, 17, (yMax /2) - (yDim /2) + 3, (xMax /2) + (xDim /2) + 8 );
        tetris = newwin(3, 12 , (yMax /2) - (yDim /2) , (xMax /2) - (xDim /2) - 22);
        box(tetris, 0, 0);
        wmove(this-> tetris, 1, 3);
        
        printColors(this-> tetris, 14, "T");
        printColors(this-> tetris, 13, "E");
        printColors(this-> tetris, 11, "T");
        printColors(this-> tetris, 12, "R");
        printColors(this-> tetris, 15, "I");
        printColors(this-> tetris, 16, "S");

        box(this->score_win, 0, 0); 
        box(this->lev_win, 0,  0);
        mvwprintw(this->score_win, 1, 1, "Highscore");
        mvwprintw(this->lev_win, 1, 1, "Lines");
        mvwprintw(this->lev_win, 3, 1, "Level");
        ifstream readscore;
        readscore.open("scores.txt");
        highscore = "0";
        const char *u;
        if(!is_empty(readscore)){
            readscore.ignore(maxc, readscore.widen('\n'));
            getline(readscore,highscore);	
        }
        u = highscore.c_str();
        wattron(lev_win, A_REVERSE);
		mvwprintw(lev_win, 2, 1, "%d",compl_lines);
        wattroff(lev_win, A_REVERSE);
        wattron(lev_win, A_REVERSE);
		mvwprintw(lev_win, 4, 1, "%d",level);
        wattroff(lev_win, A_REVERSE);
        wattron(score_win, A_REVERSE);
		mvwprintw(score_win, 2, 1, u);
        wattroff(score_win, A_REVERSE);
        mvwprintw(this->score_win, 3, 1, "Score");
        string a;
        const char * v;
        a = to_string(score);
        v = a.c_str();
        wattron(score_win, A_REVERSE);
        mvwprintw(this->score_win, 4, 1, v); 
        wattroff(score_win, A_REVERSE);
        wborder(this-> win, 0, 0, ' ', 0, ' ', ' ', 0, 0);
        mvwprintw(this-> win, 1, 0, " ");
        mvwprintw(this-> win, 2, 0, " ");
        mvwprintw(this-> win, 1, xDim +9, " ");
        mvwprintw(this-> win, 2, xDim +9, " ");
        clearboard();
        showBoard();

        winNext = newwin (8, 12, (yMax /2) - (yDim /2)+10, (xMax /2) + (xDim /2) + 10);
        winHold = newwin (8, 12, (yMax /2) - (yDim /2)+10, (xMax /2) - (xDim /2) - 22);
        box(winNext, 0, 0);
        box(winHold, 0, 0);
        mvwprintw(winNext, 0, 3 , " Next ");
        mvwprintw(winHold, 0, 3, " Hold ");
        drawNext();
        drawTetramino();
        refresh();
        wrefresh(this->winHold);
        wrefresh(this->winNext);
        wrefresh(this-> win);
        wrefresh(this-> score_win);
        wrefresh(this->lev_win);
        wrefresh(this->tetris);
    }

    bool TetrisBoard::is_empty(istream& file){
		return file.peek() == ifstream :: traits_type :: eof();
	}

    void TetrisBoard::randomTtrmn() {
        srand(time(NULL));
        // NOTE: per motivi conosciuti solo a C, rand() % n crea problemi con alcuni valori di n.
        //       Su MacOS, uno di questi e' 7, come il nostro numero di tetramini.
        //       Per evitare di sbilanciare la statistica e avere 0 e 1 che generano lo stesso tetramino,
        //       si utilizza questo metodo rapido anche se non molto elegante.
        int rndm = 0;
        while( rndm == 0 ) {
            rndm = rand() % POSS_TETRAM;
        }
        switch ( rndm ) {
            case 1:
                ttrmnNext = new Square();
                break;
            case 2:
                ttrmnNext = new Rect();
                break;
            case 3:
                ttrmnNext = new J_SHAPE();
                break;
            case 4:
                ttrmnNext = new L_SHAPE();
                break;
            case 5:
                ttrmnNext = new S_HAPE();
                break;
            case 6:
                ttrmnNext = new T_SHAPE();
                break;
            case 7:
            default:
                ttrmnNext = new Z_SHAPE();
                break;
        }
    }

    void TetrisBoard::clearboard() {
        for ( int i = 0; i < YLENGTH; i++ ) {
            for ( int j = 0; j < XLENGTH; j++ ) {
                boardArray[i][j] = -1;
            }
        }
    }

    void TetrisBoard::showBoard() {
        for ( int i = 0; i < YLENGTH; i++ ) {
            wmove(this-> win, i +1, 1);
            for ( int j = 0; j < XLENGTH; j++ ) {
                if ( boardArray[i][j] == -1 ) {
                    wprintw(this-> win, " ");
                    wprintw(this-> win, " ");
                } else {
                    printColors(this-> win, boardArray[i][j], " ");
                    printColors(this-> win, boardArray[i][j], " ");
                }
            }
        }
        wrefresh(this-> win);
        refresh();
    }

    void TetrisBoard::drawTetramino() {
        for ( int i = 0; i < 4; i++ ) {
            wmove(this-> win, yPosition +i +1, 2*(xPosition) + 1);
            for ( int j = 0; j < 4; j++ ) {
                if ( ttrmn-> ttrmnColor(i, j) == -1 ) {
                    wmove(this-> win, yPosition +i +1, 2*(xPosition) + 2*j + 3);
                } else {

                    printColors(this-> win, ttrmn-> ttrmnColor(i, j), " ");
                    printColors(this-> win, ttrmn-> ttrmnColor(i, j), " ");

                }
            }
        }
        wrefresh(this-> win);
        refresh();
    }

    void TetrisBoard::drawHold(){
        int t = ttrmn-> getType();
        Tetramino* t_p;

        switch (t) {
            case 1:
                t_p = new Square();
                break;

            case 2:
                t_p = new Rect();
                break;

            case 3:
                t_p = new J_SHAPE();
                break;

            case 4:
                t_p = new L_SHAPE();
                break;

            case 5:
                t_p = new S_HAPE();
                break;
             
            case 6:
                t_p = new T_SHAPE();
                break;

            case 7:
                t_p = new Z_SHAPE();
                break;            

            default:
                break;
        }

        wmove(winHold, 2, 3);
        for ( int i = 0; i < 4; i++ ) {
            for ( int j = 0; j < 4; j++ ) {
                if ( t_p-> ttrmnColor(i, j) == -1 ) {
                    wprintw(this-> winHold, " ");
                    wprintw(this-> winHold, " ");
                } else {
                    printColors(this-> winHold, t_p-> ttrmnColor(i, j), " ");
                    printColors(this-> winHold, t_p-> ttrmnColor(i, j), " ");
                }
            }
            wmove(winHold, 2+i+1, 3);
        }
        wrefresh(this->winHold);
        refresh();
        delete t_p;
        t_p = NULL;

    }

    void TetrisBoard::drawNext(){
        wmove(winNext, 2, 3);
        for ( int i = 0; i < 4; i++ ) {
            for ( int j = 0; j < 4; j++ ) {
                if ( ttrmnNext-> ttrmnColor(i, j) == -1 ) {
                    wprintw(this-> winNext, " ");
                    wprintw(this-> winNext, " ");
                } else {
                    printColors(this-> winNext, ttrmnNext-> ttrmnColor(i, j), " ");
                    printColors(this-> winNext, ttrmnNext-> ttrmnColor(i, j), " ");
                }
            }
            wmove(winNext, 2+i+1, 3);
        }
        wrefresh(this-> winNext);
        refresh();
    }

    int TetrisBoard::addBlock() {
        for ( int i = 0; i < ttrmn-> getMaxDim(); i++ ) {
            for ( int j = 0; j < ttrmn-> getMaxDim(); j++ ) {
                if ( ttrmn-> ttrmnColor(i, j) != -1 ) {
                    boardArray[i + yPosition][j + xPosition] = ttrmn-> getType();
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
                if ( boardArray[i][j] >= 0) {
                    name_player();
                    return -1;
                }
            }
        }
        //reset 'hold' use
        can_hold = true;
        // extract a new Tetramino
        ttrmn = ttrmnNext;
        randomTtrmn();
        xPosition = (xDim /2) - (ttrmn-> getMaxDim() /2) -1;
        return 0;
    }

    void TetrisBoard::name_player() {
        string s = "              ";
        //apriamo finestra che chiede il nome, inseriamo il nome e sovrascriviamo il file
        name_win = newwin(9, 40, yMax/2 - 3, xMax/2 - 20);
        box(name_win,0,0);
        mvwprintw(name_win, 1, 12,"Insert your name:");
       
        
        nome = newwin(3, 17, yMax/2 + 1, xMax/2 - 9);
        box(nome, 0,0);
        refresh();
        wrefresh(name_win);
        wrefresh(nome);

        int position = 0;
        int c;
        while(position < 15 && c != 27){
            c = getch();
            if ( c == KEY_BACKSPACE || c == 127 || c == '\b' ) {
                if ( position > 0 ) {
                    s[position - 1] = ' ' ;
                    mvwprintw(nome, 1, position, " ");
                    wrefresh(nome);
                    position--;
                }
            } else if ( c == 27 ||  c == '\n' || c == KEY_ENTER ) {
                if ( position > 0 ) {
                    position = 15;
                }
            } else if ( position < 14 && c != -1 && c != ' ' && c != KEY_RIGHT && c != KEY_LEFT && c != KEY_UP && c != KEY_DOWN ) {
                s[position] = c;
                mvwprintw(nome,  1, position +1, "%c", c);
                wrefresh(nome);
                position++;
            }
        }
        if ( c != 27 ) {
            bool prova;
            ifstream readscore;
            ofstream writescore;
            readscore.open("scores.txt");
            if(!readscore.is_open()) cout << "Error : opening file failed";
            if(is_empty(readscore)){
                writescore.open("scores.txt", ofstream::app);
                if(!writescore.is_open()) cout << "Error : opening file failed";
                writescore << s << endl << score ; 
            }
            else{
                string line;
                int p;
                int read_line = 1;
                int pos_line = 0;
                bool found = false;
                riga* head = new riga;
                riga* tmp = head;
                while (!readscore.eof()){
                    getline(readscore, line);
                    if (read_line % 2 == 0 ){
                        p = stoi(line);
                        if(p < score && !found){
                            found = true;
                            pos_line = read_line -1;
                        }
                        tmp-> score = p;
                        tmp-> next = new riga;
                        tmp = tmp-> next;
                    } else {
                        tmp-> name = line;
                    }
                    read_line += 1;
                }
                if (!found){
                    writescore.open("scores.txt", ofstream::app);
                    if(!writescore.is_open()) cout << "Error : opening file failed";
                    writescore << endl << s << endl << score ;
                }
                else{
                    int current_line = 1;
                    writescore.open("scores.txt");
                    if(!writescore.is_open()) cout << "Error : opening file failed";
                    tmp = head;
                    while( tmp -> next != NULL ) {
                        if ( current_line != 1 ) {
                            writescore << endl;
                        }
                        if ( current_line == pos_line ) {
                            writescore << s << endl << score << endl;
                        }
                        writescore << tmp-> name << endl << tmp-> score;
                        current_line+=2;
                        tmp = tmp-> next;
                    }
                }

            }
            readscore.close();
            writescore.close();
        }
    }

    

    bool TetrisBoard::clearUnder() {
        for ( int i = 0; i < ttrmn-> getMaxDim(); i++ ) {
            for ( int j = 0; j < ttrmn-> getMaxDim(); j++ ) {
                if ( ttrmn-> ttrmnColor(i, j) >= 0 ) {
                    if ( yPosition +i +1 == YLENGTH || boardArray[yPosition +i +1][xPosition + j] >= 0 ) {
						// TODO potential improvement, for-loop could be stopped at the first true bottom element of each column
                        return false;
                    }
                }
            }
        }
        return true;
    }

    bool TetrisBoard::clearLeft() {
        for ( int i = 0; i < ttrmn-> getMaxDim(); i++ ) {
            for ( int j = 0; j < ttrmn-> getMaxDim(); j++ ) {
                if ( ttrmn-> ttrmnColor(i,j) >=0 ) {
                    if ( xPosition +j == 0 || boardArray[yPosition +i][xPosition + j -1] >= 0) {
                        // TODO potential improvement, for-loop could be stopped at the first true left element of each row
                        return false;
                    }
                }
            }
        }
        return true;
    }

    bool TetrisBoard::clearRight() {
        for ( int i = 0; i < ttrmn-> getMaxDim(); i++ ) {
            for ( int j = 0; j < ttrmn-> getMaxDim(); j++ ) {
                if ( ttrmn->ttrmnColor(i,j) >=0 ) {
                    if ( xPosition + j + 1 == XLENGTH || boardArray[yPosition +i][xPosition + j + 1] >=0 ) {
						// TODO potential improvement, for-loop could be stopped at the first true right element of each row
                        return false;
                    }
                }
            }
        }
        return true;
    }

    bool TetrisBoard::clearRotation() {
        for ( int i = 0; i < ttrmn-> getMaxDim(); i++ ) {
            for ( int j = 0; j < ttrmn-> getMaxDim(); j++ ) {
                // controls: esiste gia' un blocco in quel posto                                                    uscirebbe dal basso         uscirebbe a destra          uscirebbe a sinistra
                if ( ( boardArray[i+yPosition][j+xPosition] >=0 && ttrmn-> ttrmnColor(i,j) >= 0 ) || ( ttrmn-> ttrmnColor(i,j) >= 0 && (i + yPosition >= YLENGTH || j + xPosition >= XLENGTH || xPosition < 0 ) ) ) {
                    return false;
                }
            }
        }
        return true;
    }

    // movements:
    int TetrisBoard::tetraFall() {
        if ( clearUnder() ) {
            yPosition++;
            return 0;
        } else {
            int r = addBlock();
            checkCompletedLines();
            return r;
        }

    }

    void TetrisBoard::checkCompletedLines(){
        int cont = 0;
        for(int y=0; y<YLENGTH; y++) {
            bool isLineCleared = true;
            for(int x=0; x< XLENGTH && isLineCleared ; x++) {
                if(boardArray[y][x] == -1) {
                    isLineCleared = false; //se trovo un "buco" esco dal for e sono sicuro di aver trovato una riga non completa
                }
            }
            if(isLineCleared) {
                if(y==0) {
                    for(int x=0; x< XLENGTH ; x++) {
                        boardArray[0][x]=-1;
                    }
                } else {
                    for(int y2=y; y2>0; y2--) {
                        for(int x2=0; x2< XLENGTH ; x2++) {
                            boardArray[y2][x2]=boardArray[y2-1][x2];
                        }
                    }
                }
                cont++;
            }
        }
        score = incr_score(cont, level);
        compl_lines+=cont; 
        if(( compl_lines-(level+1)*4 >=0) && cont!=0){ //NOTE - (level+1) non è elegante ma necessario per iniziare il gioco a lv.0 e poter comunque applicare questa formula
            if(fall_rate>MIN_RATE){   
                if(level<REF_LEV){
                    fall_rate-=FIRST_RATE;
                }
                else
                {
                    fall_rate-=SECOND_RATE;
                }
            }
            level++;
        }
        string a;
        const char *u;
        a = to_string(score);
        u = a.c_str();
        wattron(score_win, A_REVERSE);
        mvwprintw(this->score_win, 4, 1, u); 
        wattroff(score_win, A_REVERSE);
        int hs;
        hs = stoi(highscore);
        if (hs < score){
            wattron(score_win, A_REVERSE);
            mvwprintw(this->score_win, 2, 1, u); 
            wattroff(score_win, A_REVERSE);
        }
        wattron(lev_win, A_REVERSE);
		mvwprintw(lev_win, 2, 1, "%d",compl_lines);
        wattroff(lev_win, A_REVERSE);
        wattron(lev_win, A_REVERSE);
		mvwprintw(lev_win, 4, 1, "%d",level);
        wattroff(lev_win, A_REVERSE);
        wrefresh(lev_win);
        wrefresh(score_win);
    }

    int TetrisBoard::incr_score(int n, int level){
        switch(n){
            case 0:
                break;
            case 1:
                score = score + (40*(level+1));
                break;
            case 2:
                score = score + (100*(level+1));
                break;
            case 3:
                score = score + (300*(level+1));
                break;
            case 4:
                score = score + (1200*(level+1));
                break;
            default:
                break;
        }
        return score;
    }

    int TetrisBoard::getFallRate() {
        return this-> fall_rate;
    }

    void TetrisBoard::moveLeft() {
        if ( clearLeft() ) {
            xPosition--;
        }
    }

    void TetrisBoard::moveRight() {
        if ( clearRight() ) {
            xPosition++;
        }
    }

    void TetrisBoard::pigliaTetramino(){
        can_hold=false;
        if ( typeHold == -1 ) { 
            yPosition = 0; 
            drawHold();
            typeHold = ttrmn-> getType();
            delete ttrmn;
            ttrmn = NULL;
            ttrmn = ttrmnNext;
            randomTtrmn();
            xPosition  = (xDim /2) - (ttrmn-> getMaxDim() /2) -1;
        } else {
            drawHold();
            int tmp = ttrmn-> getType();

            switch (typeHold) {
                case 1:
                    ttrmn = new Square();
                    break;

                case 2:
                    ttrmn = new Rect();
                    break;

                case 3:
                    ttrmn = new J_SHAPE();
                    break;

                case 4:
                    ttrmn = new L_SHAPE();
                    break;

                case 5:
                    ttrmn = new S_HAPE();
                    break;

                case 6:
                    ttrmn = new T_SHAPE();
                    break;

                case 7:
                    ttrmn = new Z_SHAPE();
                    break;            

                default:
                    break;
            }
            typeHold = tmp;
            yPosition = 0;
            xPosition = (xDim /2) - (ttrmn-> getMaxDim() /2) -1;
        }
    }

    int TetrisBoard::fallCompletely() {
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

    TetrisBoard::TetrisBoard() {
        getmaxyx(stdscr, this-> yMax, this-> xMax);
        xDim = XLENGTH +2;
        yDim = YLENGTH +2;
        this-> win = NULL;
        this->score_win = NULL;
    }


    int TetrisBoard::getInput(int inpt) {
        int r = 0;
        switch( inpt ) {
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

            case KEY_UP: // routa in senso orario anche con la freccia in su
            case 'r':
                ttrmn-> rotate();
                if ( !clearRotation() ) {
                    ttrmn-> antiRotate();
                }
                break;
            case 'e':
                if(can_hold)
                    pigliaTetramino();
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

    void TetrisBoard::printColors(WINDOW* thisWin, short colorNumber, const char* s) {
        wattron(thisWin, COLOR_PAIR(colorNumber));
        wprintw(thisWin, s);
        wattroff(thisWin, COLOR_PAIR(colorNumber));
    }

    void TetrisBoard::reload() {
        if ( this-> win != NULL ) {
            remove();
        }
        init();
    }


    void TetrisBoard::deleteWin(WINDOW* finestra) {
        wclear(finestra);
        wrefresh(finestra);
        delwin(finestra);
        finestra = NULL;
    }

    void TetrisBoard::remove() {
        if ( this-> win != NULL ) {
            deleteWin(winNext);
            deleteWin(winHold);

            // For some reasons it crashes when you do deleteWin(this-> win);
            wclear(this-> win);
            wrefresh(this-> win);
            delwin(this-> win);
            this-> win = NULL;

            deleteWin(this-> score_win);
            deleteWin(lev_win);
            deleteWin(tetris);
            delete ttrmn;
            this-> ttrmn = NULL;
            delete ttrmnNext;
            this-> ttrmnNext = NULL;
            refresh();
        }
    }
