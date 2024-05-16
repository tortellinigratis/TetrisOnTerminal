#include "Leaderboard.hpp"


void Leaderboard::init(){
    win = newwin (16, xMax/2, yMax/4, xMax/4);  //creo la finestra
	    box(win,0,0);
	    mvwprintw( win, 0, xMax/4-7 ," Leaderboard ");
		printscores();	//Stampa nome e punteggio punteggio
	    refresh();
	    wrefresh(win);
}

void Leaderboard::printscores(){
    ifstream readscore;
		int h=3;  //g++ -I/mingw64/include/ncurses -o main main.cpp -lncurses -L/mingw64/bin -static
    	readscore.open("scores.txt");

		if(is_empty(readscore)){
			clear();
			int yMax, xMax;
			getmaxyx(win, yMax, xMax);
			mvwprintw( win, 2, xMax/2 - 6 ,"No scores yet");
			mvwprintw( win, 5, xMax/2 - 21,"You can be the top player at least for once");
		}
		else{
			if(!readscore.is_open()) cout << "Error : opening file failed";

			if(!is_empty(readscore)){

				mvwprintw( stdscr, yMax/4 + 16 , 3*(xMax/4) - 17,"Press c to clear");

				for (int i = 0; i < page; i++){						//skippo le linee che non servono 
					readscore.ignore(maxc, readscore.widen('\n'));
				}

				for (int i = 0; i < 5 && !readscore.eof(); i++ ){
					
					string a;
					const char* u;

					switch( (page /2) +1 +i ) {
						case 1:
							wattron(win, COLOR_PAIR(1)); //verde
							break;
						case 2:
							wattron(win, COLOR_PAIR(2)); // blu
							break;
						case 3:
							wattron(win, COLOR_PAIR(3)); // giallo
							break;
						default:
							break;
					}

					int classifica;
					classifica = (page / 2) + 1 + i;
					a= to_string(classifica);
					a = a + ".";
					u=a.c_str();
					mvwprintw(win, h, xMax/4-11, u);
					

					getline(readscore,a);
					u = a.c_str();
					mvwprintw(win, h, xMax/4-6, u);

					getline(readscore,a);
					u = a.c_str();
					mvwprintw(win, h, xMax/4+8, u);

					h = h + 2;
					wattroff(win, COLOR_PAIR(1));
					wattroff(win, COLOR_PAIR(2));
					wattroff(win, COLOR_PAIR(3));
				}
			}
		}
}

bool Leaderboard::is_empty(ifstream& file){
    return file.peek() == ifstream :: traits_type :: eof();
}

void Leaderboard::scrolldown(){
    int numLines = 0;
		ifstream readscore;
			readscore.open("scores.txt");
		string unused;
		while (getline(readscore, unused)) numLines++;
	
		if(numLines-N > page){	//non so perche funzioni, sono andato ad intuito
			page = page + N;
			reload();
		}
}

void Leaderboard::scrollup(){
    if(page == 0) reload();
		else{
			page = page - N;
			reload();
		}
}

void Leaderboard::readFile(){
    ifstream readscore;
		readscore.open("scores.txt");

		if(!readscore.is_open()) {
			cout << "Error : opening file failed";
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

void Leaderboard::clear_scores(){
    start_color();
		WINDOW *clear_check;
		clear_check = newwin (7, xMax/3, yMax/3 + 1, xMax/3);  //creo la finestra
	    box(clear_check,0,0);
		start_color();
		int ymax, xmax;
		getmaxyx(clear_check, ymax, xmax);
	    mvwprintw( clear_check, 0, xmax/2 -6 ," Are you sure? ");
	    refresh();
	    wrefresh(clear_check);
		keypad(clear_check, true);
		string choices[2] = {"No", "Yes"};
		int choice;
		int highlight = 0;
		bool inSure = true;
		while (inSure){
			for (int i = 0; i < 2 ; i++){
				if (i == highlight){
					wattron(clear_check, A_REVERSE);
				}	
				mvwprintw(clear_check, 4, xmax/4 + (xmax/2)*i, choices[i].c_str());
				wattroff(clear_check, A_REVERSE);
				
				
			}
			choice = wgetch (clear_check);

			switch(choice){
				case KEY_LEFT:
					highlight --;
					if(highlight == -1){
						highlight = 0;
					}
					break;
				case KEY_RIGHT:
					highlight ++;
					if (highlight == 2){
						highlight = 1;
					}
					break;
				case '\n':
					if (highlight == 1){
						ofstream readscore;
						readscore.open("scores.txt", ofstream :: out | ofstream :: trunc);
						readscore.close();
						page=0;
					}
					wclear(clear_check);
					wrefresh(clear_check);
					delwin(clear_check);
					clear_check = NULL;
					refresh();
					inSure = false;
					reload();

				default:
					break;
			}
		}
}

Leaderboard::p_pos Leaderboard::head_insert(p_pos head,  string user, int score){
        p_pos tmp = new pos;
        tmp->username = user;
        tmp->score = score;
        tmp->next = head;
		return tmp;
}

Leaderboard::Leaderboard(){
    getmaxyx(stdscr, yMax, xMax);
    win = NULL;
}

void Leaderboard::remove(){
		if ( this-> win != NULL ) {
			wclear(this-> win);
			wrefresh(this-> win);
			delwin(this-> win);
			this-> win = NULL;
			refresh();
		}
	}

void Leaderboard::reload() {
	    if (win != NULL)
		    remove();
	    init();
    }

int Leaderboard::getInput(){
		bool inLeaderboard = true;
		while(inLeaderboard){
			switch (getch()){
				case 27:  //esc=27
					clear();
					inLeaderboard = false;
					page = 0;
					wclear(win);
					wrefresh(win);
					break;

				case KEY_DOWN:
					scrolldown();
					break;

				case KEY_UP:
					scrollup();
					break;

				case 'c':
				{
					ifstream readscore;
					readscore.open("scores.txt");
					if (!is_empty(readscore)){
						clear_scores();
					}
					
					break;
				}

				default:
					break;
			
			}
		}
		return -1;
	}

