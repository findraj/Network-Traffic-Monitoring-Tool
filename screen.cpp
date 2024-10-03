/**
 * ISA Project 2024
 * 
 * @file screen.cpp
 * @brief Screen functions
 * 
 * @author Jan Findra (xfindr01)
 */

#include "screen.h"

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

void printLine(int row, connection conn){
    int width = getmaxx(stdscr) / 5;
    mvprintw(row, 0, "%s:%s", conn.srcIP.c_str(), conn.srcPort.c_str());
    mvprintw(row, width, "%s:%s", conn.dstIP.c_str(), conn.dstPort.c_str());
    mvprintw(row, width * 2, "%s", conn.proto.c_str());
    mvprintw(row, width * 3, "%d", conn.rxbps);
    mvprintw(row, width * 3.5, "%d", conn.rxpps);
    mvprintw(row, width * 4, "%d", conn.txbps);
    mvprintw(row, width * 4.5, "%d", conn.txpps);
}

void printScreen(){
    printHeader();
    connection test = {"147.229.13.210", "443", "147.229.14.76", "61027", "tcp", 130, 62, 10, 1};
    printLine(2, test);
    refresh();
    getch();
}

void closeScreen(){
    endwin();
}