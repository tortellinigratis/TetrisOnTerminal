#include <iostream>
#include <fstream>
#include <ncurses.h>
#include <cstring>
using namespace std;

// TODO empty file case

class Leaderboard{
private:
    int yMax, xMax;
    WINDOW * win;
	struct pos{
		string username;
		int score;
		pos *next;
	};
	typedef pos* p_pos;
    void init(){
		win = newwin (10, xMax/2, yMax/4, xMax/4);  //creo la finestra
	    box(win,0,0);
	    mvwprintw( win, 0, xMax/4-5 ,"leaderboard");
	    refresh();
	    wrefresh(win);
    }

	void readFile(){
		ifstream readscore;
		readscore.open("scores.txt");

		if(!readscore.is_open()) {
			cout << "Errore nell' apertura del file";
			// REVIEW error handling
		}

		p_pos head = NULL;

		while(!readscore.eof()){        //salvo nella lista le informazioni (FUNZIONA!)
			string p1;
			getline(readscore, p1);

			string p2;
			getline(readscore, p2);
			int p3 = stoi(p2);

			head = head_insert(head,p1,p3);
		}
		readscore.close();
	}

    p_pos head_insert(p_pos head,  string user, int score){
        p_pos tmp = new pos;
        tmp->username = user;
        tmp->score = score;
        tmp->next = head;
		return tmp;
    }

public:
    Leaderboard(){
        getmaxyx(stdscr, yMax, xMax);
        win = NULL;
    }

	void remove(){
		if ( this-> win != NULL ) {
			wclear(this-> win);
			wrefresh(this-> win);
			delwin(this-> win);
			this-> win = NULL;
			refresh();
		}
	}

    void reload() {
	    if (win != NULL)
		    remove();
	    init();
    }


};