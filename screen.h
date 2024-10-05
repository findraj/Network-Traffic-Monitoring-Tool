/**
 * ISA Project 2024
 * 
 * @file screen.h
 * @brief Screen functions
 * 
 * @author Jan Findra (xfindr01)
 */

#include <ncurses.h>
#include <string>
#include <vector>

using namespace std;

struct connection
{
    string srcIP;
    string srcPort;
    string dstIP;
    string dstPort;
    string proto;
    int rxbps;
    int rxpps;
    int txbps;
    int txpps;
};


void initScreen();

void printHeader();

void printLine(int row, connection conn);

void printScreen(vector<connection> connections);

void closeScreen();