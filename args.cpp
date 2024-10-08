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
        if (!isdigit(c)) // if the character is not a digit
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
                    if (currentArg == "b") // if the switch is b set bytes to true
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
                if (i + 1 < argc) // check if there is another argument which is the frequency
                {
                    currentArg = argv[i + 1]; // get the time
                    if (isNumber(currentArg)) // check if the time is a number
                    {
                        // set the time
                        arguments.freq = stoi(currentArg);
                    }
                    else
                    {
                        printError("Frequency is not a number", false, NULL);
                    }
                    i++;
                }
                else // time not specified
                {
                    printError("Time not specified", false, NULL);
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