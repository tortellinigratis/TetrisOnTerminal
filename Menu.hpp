#ifndef MENU_HPP
#define MENU_HPP

#include <string.h>
#include <iostream>
#include "platform.hpp"

using namespace std;

#define OPTIONS 3

class Menu {
private:
    int index;
    char options[OPTIONS][12];
    int yMax, xMax;
    WINDOW* win;

    void init();
    
    void writeTitle();
    void titleAttributes(int n, const char* c);

    void writeOptions();

public:
    Menu();

    int getInput();

    void update();

    void reload();

    void remove();
};
#endif