#ifndef LEADERBOARD_HPP
#define LEADERBOARD_HPP

#include <iostream>
#include <fstream>
#include <cstring>
#include "platform.hpp"
#define N 10
#define maxc 15
using namespace std;

class Leaderboard{

private:  
	struct pos{
		string username;
		int score;
		pos *next;
    };
	typedef pos* p_pos;

    int yMax, xMax, page;
    WINDOW * win;

    void init();

    void printscores();
	bool is_empty(ifstream&);
	
	void scrolldown();
	void scrollup();
	
	void clear_scores();

public:
    Leaderboard();
	void remove();
    void reload();
	int getInput();
};

#endif
