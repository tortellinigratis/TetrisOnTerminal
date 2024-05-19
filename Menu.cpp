#include "Menu.hpp"
void Menu::writeTitle() {
        wmove(this-> win, 0, xMax /4 -3);
        wprintw(this-> win, this-> title);
    }

void Menu::writeOptions() {
        for ( int i = 0; i < OPTIONS; i++ ) {
            wmove(this-> win, (yMax /4 -3) +(i *2), 6);
            if ( i == this-> index ) {
                wattron(this-> win, A_REVERSE);
            }
            wprintw(this-> win, options[i]);
            wattroff(this-> win, A_REVERSE);
        }
    }

void Menu::init() {
        getmaxyx(stdscr, this-> yMax, this-> xMax);
        this-> index = 0;
        this-> win = newwin(yMax /2, xMax /2, yMax /4, xMax /4);
        update();
    }
Menu::Menu() {
        strcpy(this-> title, " Menu ");
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
        box(this-> win, 0, 0);
        writeTitle();
        writeOptions();
        render();
    }

void Menu::render() {
        if ( this-> win != NULL ) {
            refresh();
            wrefresh(this-> win);
        } else {
            init();
        }
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