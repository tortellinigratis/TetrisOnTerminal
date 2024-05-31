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
    WINDOW* win;
    int index;
    char options[OPTIONS][12];

    void writeTitle();

    void titleAttributes(int n, const char* c);

    void writeOptions();

    void init();

public:
    Menu();

    int getInput() ;

    void update() ;

    void reload();

    void remove();
};
#endif