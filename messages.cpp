/**
 * ISA Project 2024
 * 
 * @file messages.cpp
 * @brief Functions for printing messages/errors
 * 
 * @author Jan Findra (xfindr01)
 */

#include "messages.h"

void printHelp() {
    cout << "Usage: ./isa-top -i interface [-s b|p]" << endl
    << "Options:" << endl
    << "  -i interface  Interface to listen on" << endl
    << "  -s b|p        Type of speed to be ordered by" << endl
    << "                b - number of bytes per second (B/s)" << endl
    << "                p - number of packets per second (packet/s)" << endl
    << "Note: The program might require root privileges to run" << endl;
}
// TODO: closing properly
void printError(string message, bool closeScr, pcap_t *handle) {
    cerr << "Error: " << message << endl << endl;
    printHelp();
    if (closeScreen) {
        closeScreen();
    }
    if (handle != NULL) {
        pcap_close(handle);
    }
    exit(1);
}