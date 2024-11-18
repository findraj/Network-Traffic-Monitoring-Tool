/**
 * ISA Project 2024
 *
 * @file main.h
 * @brief Main file of the project
 *
 * @author Jan Findra (xfindr01)
 */

#include <stdio.h>
#include <signal.h>
#include <thread>
#include <atomic>
#include <mutex>
#include "args.h"

/**
 * @brief Function to handle signals, especially SIGINT
 *
 * @param signum Signal number
 */
void signalHandler(int signum);

/**
 * @brief Function to handle screen printing and preparing data for printing
 *
 */
void screenHandler();

/**
 * @brief Function to call other functions necessary for packet handling
 *
 * @param userData User data
 * @param pkthdr Packet header
 * @param packet Packet
 */
void pHandler(u_char *userData, const struct pcap_pkthdr *pkthdr, const u_char *packet);

/**
 * @brief Main function
 *
 * @param argc Number of arguments
 * @param argv Arguments in array
 * @return int Return code
 */
int main(int argc, char *argv[]);