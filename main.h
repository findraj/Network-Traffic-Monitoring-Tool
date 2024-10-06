/**
 * ISA Project 2024
 * 
 * @file main.h
 * @brief Main file of the project
 * 
 * @author Jan Findra (xfindr01)
 */

#include <stdio.h>
#include <unistd.h>
#include "args.h"

void pHandler(u_char *userData, const struct pcap_pkthdr* pkthdr, const u_char* packet);

/**
 * @brief Main function
 * 
 * @param argc Number of arguments
 * @param argv Arguments in array
 * @return int Return code
 */
int main(int argc, char *argv[]);