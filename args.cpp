/**
 * ISA Project 2024
 *
 * @file args.cpp
 * @brief Structure and function for parsing arguments
 *
 * @author Jan Findra (xfindr01)
 */

#include "args.h"

bool isNumber(string str)
{
    for (char c : str) // go through all characters
    {
        // if the character is not a digit return false
        if (!isdigit(c))
        {
            return false;
        }
    }

    return true;
}

args parseArgs(int argc, char *argv[])
{
    args arguments;

    if (argc < 3) // if there are not enough arguments
    {
        printError("Interface not specified", false, NULL);
    }
    else // if there are enough arguments
    {
        for (int i = 1; i < argc; i++) // go through all arguments
        {
            string currentArg = argv[i]; // get the current argument
            if (currentArg == "-i")
            {
                if (i + 1 < argc) // check if there is another argument which is the interface
                {
                    arguments.interface = argv[i + 1]; // set the interface
                    i++;
                }
                else // interface not specified
                {
                    printError("Interface not specified", false, NULL);
                }
            }
            else if (currentArg == "-s")
            {
                if (i + 1 < argc) // check if there is another argument which is the switch
                {
                    currentArg = argv[i + 1]; // get the switch
                    if (currentArg == "b")    // if the switch is b set bytes to true
                    {
                        arguments.bytes = true;
                    }
                    else if (currentArg == "p") // if the switch is p set bytes to false
                    {
                        arguments.bytes = false;
                    }
                    else
                    {
                        printError("Unknown argument for this switch", false, NULL);
                    }
                    i++;
                }
                else // switch not specified
                {
                    printError("Switch not specified", false, NULL);
                }
            }
            else if (currentArg == "-t")
            {
                if (i + 1 < argc) // check if there is another argument which is the period
                {
                    currentArg = argv[i + 1]; // get the period
                    if (isNumber(currentArg)) // check if the period is a number
                    {
                        // set the period
                        arguments.period = stoi(currentArg);
                    }
                    else
                    {
                        printError("Period is not an integer", false, NULL);
                    }
                    if (arguments.period < 1) // check if the period is greater than 0
                    {
                        printError("Period must be greater than 0", false, NULL);
                    }
                    i++;
                }
                else // period not specified
                {
                    printError("Period not specified", false, NULL);
                }
            }
            else // unknown argument
            {
                printError("Unknown argument", false, NULL);
            }
        }
    }

    return arguments;
}