/**
 * ISA Project 2024
 * 
 * @file messages.h
 * @brief Functions for printing messages/errors
 * 
 * @author Jan Findra (xfindr01)
 */

#include <stdio.h>
#include <iostream>
#include <string>
#include <pcap.h>
#include "screen.h"

using namespace std;

/**
 * @brief Print help message
 */
void printHelp();

/**
 * @brief Print error message
 * 
 * @param message Error message
 * @param closeScr True if the screen should be closed
 * @param handle Handle to pcap, NULL if not needed
 */
void printError(string message, bool closeScr, pcap_t *handle);