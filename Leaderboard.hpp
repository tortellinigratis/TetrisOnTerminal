#ifndef LEADERBOARD_HPP
#define LEADERBOARD_HPP

#include <iostream>
#include <fstream>
#include <cstring>
#include "ncrss.cpp"
#define N 10
#define maxc 15
using namespace std;


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
    void init();
    void printscores();
	bool is_empty(ifstream& );
	void scrolldown();
	void scrollup();
	void readFile();
	void clear_scores();
    p_pos head_insert(p_pos ,  string , int );
     

public:
   

    Leaderboard();
	void remove();
    void reload();
	int getInput();
};

#endif
