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
    char tmp[32]; // buffer for the number

    if (number >= 1000000) // if the number is in millions
    {
        snprintf(tmp, sizeof(tmp), "%.1fM", number / 1000000);
    }
    else if (number >= 1000) // if the number is in thousands
    {
        snprintf(tmp, sizeof(tmp), "%.1fK", number / 1000);
    }
    else
    {
        snprintf(tmp, sizeof(tmp), "%.1f", number);
    }

    return string(tmp);
}

void initScreen()
{
    initscr();
}

void printHeader()
{
    int width = getmaxx(stdscr) / 5;         // width of one column
    mvprintw(0, 0, "%s", "Src IP:port");     // source IP and port
    mvprintw(0, width, "%s", "Dst IP:port"); // destination IP and port
    mvprintw(0, width * 2, "%s", "Proto");   // protocol
    mvprintw(0, width * 3, "%s", "Rx");      // received
    mvprintw(0, width * 4, "%s", "Tx");      // transmitted
    mvprintw(1, width * 3, "%s", "b/s");     // bytes per second
    mvprintw(1, width * 3.5, "%s", "p/s");   // packets per second
    mvprintw(1, width * 4, "%s", "b/s");     // bytes per second
    mvprintw(1, width * 4.5, "%s", "p/s");   // packets per second
}

void printIPandPort(bool ipv4, string ip, string port, int row, int col)
{
    if (port == "") // if the port is not specified
    {
        if (ipv4) // if the IP is IPv4
        {
            mvprintw(row, col, "%s", ip.c_str());
        }
        else // if the IP is IPv6
        {
            mvprintw(row, col, "[%s]", ip.c_str());
        }
    }
    else // if the port is specified
    {
        if (ipv4) // if the IP is IPv4
        {
            mvprintw(row, col, "%s:%s", ip.c_str(), port.c_str());
        }
        else // if the IP is IPv6
        {
            mvprintw(row, col, "[%s]:%s", ip.c_str(), port.c_str());
        }
    }
}

void printLine(int row, connection conn)
{
    int width = getmaxx(stdscr) / 5;                                     // width of one column
    printIPandPort(conn.ipv4, conn.srcIP, conn.srcPort, row, 0);         // source IP and port
    printIPandPort(conn.ipv4, conn.dstIP, conn.dstPort, row, width);     // destination IP and port
    mvprintw(row, width * 2, "%s", conn.proto.c_str());                  // protocol
    mvprintw(row, width * 3, "%s", floatToString(conn.rxbps).c_str());   // received bytes per second
    mvprintw(row, width * 3.5, "%s", floatToString(conn.rxpps).c_str()); // received packets per second
    mvprintw(row, width * 4, "%s", floatToString(conn.txbps).c_str());   // transmitted bytes per second
    mvprintw(row, width * 4.5, "%s", floatToString(conn.txpps).c_str()); // transmitted packets per second
}

void printScreen(vector<connection> *connections)
{
    clear(); // clear the screen to remove old data
    printHeader();
    int limit; // limit of connections to print

    if (connections->size() < 10) // if there are less than 10 connections to prevent segmentation fault
    {
        limit = connections->size();
    }
    else
    {
        limit = 10;
    }

    for (int i = 0; i < limit; i++) // print the connections
    {
        printLine(i + 2, connections->at(i));
    }

    refresh();
}

void closeScreen()
{
    endwin();
}