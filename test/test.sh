#!/bin/bash

# ISA Project 2024

# file: test.sh
# brief: Script for testing the program arguments handling
# author: Jan Findra (xfindr01)

echo "NOTE: program may need to be run as root to access the network interface"

# clean the build directory
make clean

# build the program
make

# check if the build succeeded
if [ $? -eq 0 ]; then
    printf "\e[32mBuild succeeded\e[0m\n"
else
    printf "\e[31mBuild failed\e[0m\n"
    exit 1
fi

# find the active network interface
# command may not work on all systems
interface=$(ip link show | awk '/state UP/ {print $2}' | sed 's/://; q')
# if the command cannot find the interface, exit
if [ -z "$interface" ]; then
    printf "\e[31mNo network interface found\e[0m\nPlease specify the interface manually\n"
    exit 1
fi

program="./isa-top"

successCounter=0
failCounter=0

# function for running a test
# arguments:
#   description: description of the test
#   command: command to run
#   expectedReturnCode: expected return code of the command
#   teardown: command to run after the test, if needed
runTest() {
    local description=$1
    local command=$2
    local expectedReturnCode=$3
    local teardown=$4

    printf "\e[34m%s\e[0m\n" "$description"
    echo "$command"
    eval "$command"
    local returnCode=$?
    eval "$teardown"
    wait $!

    if [ $returnCode -eq "$expectedReturnCode" ]; then
        printf "\e[32m%s succeeded\e[0m\n" "$description"
        successCounter=$((successCounter+1))
    else
        printf "\e[31m%s failed\e[0m\n" "$description"
        failCounter=$((failCounter+1))
    fi

    echo ""
}

# Test cases
runTest "Test 1: No arguments" "$program" 1
runTest "Test 2: Arguments: -i" "$program -i" 1
runTest "Test 3: Arguments: -s" "$program -s" 1
runTest "Test 4: Arguments: -t" "$program -t" 1
runTest "Test 5: Arguments: -i interface" "$program -i $interface &" 0 "kill -9 \$!"
runTest "Test 6: Arguments: -s b" "$program -s b" 1
runTest "Test 7: Arguments: -t 10" "$program -t 10" 1
runTest "Test 8: Arguments: -i interface -s b" "$program -i $interface -s b &" 0 "kill -9 \$!"
runTest "Test 9: Arguments: -i interface -s p" "$program -i $interface -s p &" 0 "kill -9 \$!"
runTest "Test 10: Arguments: -i interface -s a" "$program -i $interface -s a" 1
runTest "Test 11: Arguments: -i interface -t 10" "$program -i $interface -t 10 &" 0 "kill -9 \$!"
runTest "Test 12: Arguments: -i interface -t 0" "$program -i $interface -t 0" 1
runTest "Test 13: Arguments: -i interface -s b -t 10" "$program -i $interface -s b -t 10 &" 0 "kill -9 \$!"
runTest "Test 14: Arguments: -i interface -s p -t 10" "$program -i $interface -s p -t 10 &" 0 "kill -9 \$!"
runTest "Test 15: Arguments: -i interface -s a -t 10" "$program -i $interface -s a -t 10" 1

printf "\e[32mTests succeeded: %d\e[0m\n" "$successCounter"
printf "\e[31mTests failed: %d\e[0m\n" "$failCounter"