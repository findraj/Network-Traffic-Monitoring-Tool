/**
 * ISA Project 2024
 * 
 * @file args.h
 * @brief Structure and function for parsing arguments
 * 
 * @author Jan Findra (xfindr01)
 */

#include <cctype>
#include "packetHandler.h"

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
    int freq = 1;
};

bool isNumber(string str);

/**
 * @brief Parse arguments
 * 
 * @param argc Number of arguments
 * @param argv Arguments in array
 * @return args Arguments structure
 */
args parseArgs(int argc, char *argv[]);