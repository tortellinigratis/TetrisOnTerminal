#ifndef MENU_HPP
#define MENU_HPP

#include <string.h>
#include <iostream>
#include "ncrss.cpp"

using namespace std;

#define OPTIONS 3

class Menu {
private:
    int yMax, xMax;
    char title[7];
    WINDOW* win;
    int index;
    char options[OPTIONS][12];

    void writeTitle();

    void writeOptions();

    void init();

public:
    Menu();

    int getInput() ;
    // REVIEW potential semplification, check if these functions are actually used and how
    void update() ;

    void render();

    void reload();

    void remove();
};
#endif