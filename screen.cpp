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
    int protoWidth = 8;                                                    // width of the protocol column, 6 is the longest protocol name (icmpv6) + 2 spaces
    int speedWidth = 8;                                                    // width of the speed columns, 6 is the longest speed (xxx.xu) + 2 spaces
    int addrWidth = (getmaxx(stdscr) - protoWidth - speedWidth * 4) / 2;   // width of the address columns
    mvprintw(0, 0, "%s", "Src IP:port");                                   // source IP and port
    mvprintw(0, addrWidth, "%s", "Dst IP:port");                           // destination IP and port
    mvprintw(0, addrWidth * 2, "%s", "Proto");                             // protocol
    mvprintw(0, addrWidth * 2 + protoWidth, "%s", "Rx");                   // received
    mvprintw(0, addrWidth * 2 + protoWidth + speedWidth * 2, "%s", "Tx");  // transmitted
    mvprintw(1, addrWidth * 2 + protoWidth, "%s", "b/s");                  // bytes per second
    mvprintw(1, addrWidth * 2 + protoWidth + speedWidth, "%s", "p/s");     // packets per second
    mvprintw(1, addrWidth * 2 + protoWidth + speedWidth * 2, "%s", "b/s"); // bytes per second
    mvprintw(1, addrWidth * 2 + protoWidth + speedWidth * 3, "%s", "p/s"); // packets per second
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
    int protoWidth = 8;                                                                                  // width of the protocol column, 6 is the longest protocol name (icmpv6) + 2 spaces
    int speedWidth = 8;                                                                                  // width of the speed columns, 6 is the longest speed (xxx.xu) + 2 spaces
    int addrWidth = (getmaxx(stdscr) - protoWidth - speedWidth * 4) / 2;                                 // width of the address columns
    printIPandPort(conn.ipv4, conn.srcIP, conn.srcPort, row, 0);                                         // source IP and port
    printIPandPort(conn.ipv4, conn.dstIP, conn.dstPort, row, addrWidth);                                 // destination IP and port
    mvprintw(row, addrWidth * 2, "%s", conn.proto.c_str());                                              // protocol
    mvprintw(row, addrWidth * 2 + protoWidth, "%s", floatToString(conn.rxbps).c_str());                  // received bytes per second
    mvprintw(row, addrWidth * 2 + protoWidth + speedWidth, "%s", floatToString(conn.rxpps).c_str());     // received packets per second
    mvprintw(row, addrWidth * 2 + protoWidth + speedWidth * 2, "%s", floatToString(conn.txbps).c_str()); // transmitted bytes per second
    mvprintw(row, addrWidth * 2 + protoWidth + speedWidth * 3, "%s", floatToString(conn.txpps).c_str()); // transmitted packets per second
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