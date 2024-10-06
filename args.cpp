/**
 * ISA Project 2024
 * 
 * @file args.cpp
 * @brief Structure and function for parsing arguments
 * 
 * @author Jan Findra (xfindr01)
 */

#include "args.h"

args parseArgs(int argc, char *argv[]) {
    args arguments;
    if (argc < 3) {
        printError("Interface not specified", false, NULL);
    }
    else {
        for (int i = 1; i < argc; i++) {
            string currentArg = argv[i];
            if (currentArg == "-i") {
                if (i + 1 < argc) {
                    arguments.interface = argv[i + 1];
                    i++;
                }
                else {
                    printError("Interface not specified", false, NULL);
                }
            }
            else if (currentArg == "-s") {
                if (i + 1 < argc) {
                    currentArg = argv[i + 1];
                    if (currentArg == "b") {
                        arguments.bytes = true;
                    }
                    else if (currentArg == "p") {
                        arguments.bytes = false;
                    }
                    else {
                        printError("Unknown argument for this switch", false, NULL);
                    }
                    i++;
                }
                else {
                    printError("Switch not specified", false, NULL);
                }
            }
            else {
                printError("Unknown argument", false, NULL);
            }
        }
    }
    return arguments;
}