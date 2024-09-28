/**
 * ISA Project 2024
 * 
 * @file args.h
 * @brief Structure and function for parsing arguments
 * 
 * @author Jan Findra (xfindr01)
 */

#include "messages.h"

using namespace std;

/**
 * @brief Arguments structure
 * 
 * @param interface Interface name
 * @param bytes True if bytes, false if packets
 */
struct args
{
    string interface = "";
    bool bytes = true;
};

args parseArgs(int argc, char *argv[]);