/**
 * ISA Project 2024
 * 
 * @file main.cpp
 * @brief Main file of the project
 * 
 * @author Jan Findra (xfindr01)
 */

#include "main.h"

int main(int argc, char *argv[]) {
    args arguments = parseArgs(argc, argv);

    initScreen();
    printScreen();
    closeScreen();

    return 0;
}