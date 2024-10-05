/**
 * ISA Project 2024
 * 
 * @file screen.cpp
 * @brief Screen functions
 * 
 * @author Jan Findra (xfindr01)
 */

#include "screen.h"

string floatToString(float number)
{
    char tmp[32];

    if (number > 1000)
    {
        snprintf(tmp, sizeof(tmp), "%.1fK", number / 1000);
    }
    else if (number > 1000000)
    {
        snprintf(tmp, sizeof(tmp), "%.1fM", number / 1000000);
    }
    else
    {
        snprintf(tmp, sizeof(tmp), "%.1f", number);
    }

    return string(tmp);
}

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
    mvprintw(row, width * 3, "%s", floatToString(conn.rxbps).c_str());
    mvprintw(row, width * 3.5, "%s", floatToString(conn.rxpps).c_str());
    mvprintw(row, width * 4, "%s", floatToString(conn.txbps).c_str());
    mvprintw(row, width * 4.5, "%s", floatToString(conn.txpps).c_str());
}

void printScreen(map<string, connection> *connections){
    clear();
    printHeader();
    // connection test = {"147.229.13.210", "443", "147.229.14.76", "61027", "tcp", 130, 62, 10, 1};
    // printLine(2, test);
    printLine(2, connections->rbegin()->second);
    refresh();
}

void closeScreen(){
    endwin();
}