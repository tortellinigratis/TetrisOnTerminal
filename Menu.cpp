#include "Menu.hpp"

void Menu::writeTitle() {
        //prima linea
        wmove(this-> win, yMax/4, xMax/2 - 22 + 1);
        titleAttributes(14, "_____   ");
        titleAttributes(13, "_____   ");
        titleAttributes(11, "_____   ");
        titleAttributes(12, "____    ");
        titleAttributes(15, "___   ");
        titleAttributes(16, "____");
        //seconda linea
        wmove(this-> win, yMax/4 + 1, xMax/2 - 22);
        titleAttributes(14, "|_   _| ");
        titleAttributes(13, "| ____| ");
        titleAttributes(11, "|_   _| ");
        titleAttributes(12, "|  _ \\  ");
        titleAttributes(15,"|_ _| ");
        titleAttributes(16, "/ ___|");
        //terza linea
        wmove(this-> win, yMax/4 + 2, xMax/2 - 22 + 2);
        titleAttributes(14, "| |   ");
        titleAttributes(13, "|  _|     ");
        titleAttributes(11, "| |   ");
        titleAttributes(12, "| |_) |  ");
        titleAttributes(15, "| |  ");
        titleAttributes(16, "\\___ \\");
        //quarta linea
        wmove(this-> win, yMax/4 + 3, xMax/2 - 22 + 2);
        titleAttributes(14, "| |   ");
        titleAttributes(13, "| |___    ");
        titleAttributes(11, "| |   ");
        titleAttributes(12, "|  _ <   ");
        titleAttributes(15,"| |   ");
        titleAttributes(16, "___) |");
        //quinta linea
        wmove(this-> win, yMax/4 + 4, xMax/2 - 22 + 2);
        titleAttributes(14, "|_|   ");
        titleAttributes(13, "|_____|   ");
        titleAttributes(11, "|_|   ");
        titleAttributes(12, "|_| \\_\\ ");
        titleAttributes(15,"|___| ");
        titleAttributes(16, "|____/");
    }

    void Menu::titleAttributes(int n, const char* c) {
        wattron(this->win, COLOR_PAIR(n));
        wprintw(this-> win, c);
        wattroff(this->win,COLOR_PAIR(n));
    }

void Menu::writeOptions() {
        string a;
        a='>';
        for ( int i = 0; i < OPTIONS; i++ ) {
            int l = strlen(options[i]);
            wmove(this-> win, (yMax /4 + 8) +(i *2), (xMax/2) - (l/2) );
            if ( i == this-> index ) {
                wprintw(this-> win, a.c_str());
            }
            
            wprintw(this-> win, options[i]);
        }
    }

void Menu::init() {
        getmaxyx(stdscr, this-> yMax, this-> xMax);
        this-> index = 0;
        this-> win = newwin(yMax, xMax, 0, 0);
        update();
    }
Menu::Menu() {
        strcpy(this-> options[0], "Play");
        strcpy(this-> options[1], "Leaderboard");
        strcpy(this-> options[2], "Exit");
        this-> win = NULL;
        // nothing to see here;
    }

int Menu::getInput() {
        switch (getch()) {
            case KEY_DOWN:
                if ( index < OPTIONS -1 ) {
                    index++;
                } else {
                    index = 0;
                }
                update();
                break;

            case KEY_UP:
                if ( index > 0 ) {
                    index--;
                } else {
                    index = OPTIONS -1;
                }
                update();
                break;

            case KEY_RIGHT:
            case '\n':
                return this-> index;

            case 27:
                return 2;
        
            default:
                break;
        }
        return -1;
    }
void Menu::update() {
        wclear(this-> win);
        char c;
        c = ' ';
        // wborder(this-> win, int(c), int(c), int(c), int(c), int(c), int(c), int(c), int(c));
        writeTitle();
        writeOptions();
        refresh();
        wrefresh(this-> win);
    }

void Menu::reload() {
        if ( this-> win != NULL ) {
            remove();
        }
        init();
    }

void Menu::remove() {
        if ( this-> win != NULL ) {
            wclear(this-> win);
            wrefresh(this-> win);
            delwin(this-> win);
            this-> win = NULL;
            refresh();
        }
    } 