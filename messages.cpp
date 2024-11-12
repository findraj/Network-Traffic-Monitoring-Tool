/**
 * ISA Project 2024
 *
 * @file messages.cpp
 * @brief Functions for printing messages/errors
 *
 * @author Jan Findra (xfindr01)
 */

#include "messages.h"

void printHelp()
{
    cout << "Usage: ./isa-top -i interface [-s b|p] [-t seconds]" << endl
         << "Options:" << endl
         << "   -i interface    Interface to listen on" << endl
         << "   -s b|p          Type of speed to be ordered by" << endl
         << "                   b - number of bytes per second (B/s)" << endl
         << "                   p - number of packets per second (packet/s)" << endl
         << "                   Default is b" << endl
         << "   -t seconds      Period in seconds between updates" << endl
         << "                   Default is 1" << endl
         << "Note: The program might require root privileges to run" << endl;
}

void printError(string message, bool closeScr, pcap_t *handle)
{
    cerr << "Error: " << message << endl
         << endl; // print the error message
    printHelp();  // print the help message
    if (closeScr) // if the screen should be closed
    {
        closeScreen();
    }
    if (handle != NULL) // if the handle is not NULL
    {
        pcap_close(handle);
    }
    exit(1); // exit the program with error code
}