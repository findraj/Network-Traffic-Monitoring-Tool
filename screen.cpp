/**
 * ISA Project 2024
 * 
 * @file screen.cpp
 * @brief Screen functions
 * 
 * @author Jan Findra (xfindr01)
 */

#include "screen.h"

using namespace std;

void initScreen(){
    initscr();
}

void printHeader(){
    int width = getmaxx(stdscr) / 5;
    mvprintw(0, 0, "%s", "Src IP:port");
    mvprintw(0, width, "%s", "Dst IP:port");
    mvprintw(0, width * 2, "%s", "Proto");
    mvprintw(0, width * 3, "%s", "Rx");
    mvprintw(0, width * 4, "%s", "Tx");
    mvprintw(1, width * 3, "%s", "b/s");
    mvprintw(1, width * 3.5, "%s", "p/s");
    mvprintw(1, width * 4, "%s", "b/s");
    mvprintw(1, width * 4.5, "%s", "p/s");
}

void printScreen(){
    printHeader();
    refresh();
    getch();
}

void closeScreen(){
    endwin();
}