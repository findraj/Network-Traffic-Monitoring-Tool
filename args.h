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
 * @param freq Frequency of updates, time between updates
 */
struct args
{
    string interface = "";
    bool bytes = true;
    int freq = 1;
};

/**
 * @brief Function to check if the string is a number
 *
 * @param str String to check
 * @return True if the string is a number
 */
bool isNumber(string str);

/**
 * @brief Parse arguments
 *
 * @param argc Number of arguments
 * @param argv Arguments in array
 * @return args Arguments structure
 */
args parseArgs(int argc, char *argv[]);