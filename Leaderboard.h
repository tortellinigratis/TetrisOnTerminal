#include <iostream>
#include <fstream>
#include <ncurses/ncurses.h>
//#include <ncurses.h>
#include <cstring>
using namespace std;

// TODO empty file case
#define N 11

class Leaderboard{
private:
    int yMax, xMax, page=0;
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
		printscores();	//Stampa nome e punteggio punteggio
	    refresh();
	    wrefresh(win);
    }

	void printscores(){
		ifstream readscore;
		int h=3;
    	readscore.open("scores.txt");

    	if(!readscore.is_open()) cout << "Errore nell' apertura del file";

		for (int i = 0; i < page-1; i++){						//skippo le linee che non servono 
			readscore.ignore(100, readscore.widen('\n'));
		}

		for (int i = page-5; i < page; i++ && !readscore.eof()){
			
			string a;
			const char* u;
		
			getline(readscore,a);
			u = a.c_str();
			mvwprintw(win, h, xMax/4-6, u);

			getline(readscore,a);
			u = a.c_str();
			mvwprintw(win, h, xMax/4+8, u);

			h++;
		}
	}

	void scrolldown(){
		int numLines = 0;
		ifstream readscore;
			readscore.open("scores.txt");
		string unused;
		while (getline(readscore, unused)) numLines++;
	
		if(numLines-N >= page){	//non so perche funzioni, sono andato ad intuito
			page = page + N;
			reload();
		}
	}

	void scrollup(){
		if(page == 0) reload();
		else{
			page = page - N;
			reload();
		}
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

	int getInput(){
		bool inLeaderboard = true;
		while(inLeaderboard){
			switch (getch()){
				case 27:
					inLeaderboard = false;
					break;

				case KEY_DOWN:
					scrolldown();
					break;

				case KEY_UP:
					scrollup();
					break;

				default:
					break;
			
			}
		}
		return -1;
	}


};