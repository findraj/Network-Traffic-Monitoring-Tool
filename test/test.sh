#!/bin/bash

make

if [ $? -eq 0 ]; then
    echo "Build succeeded"
else
    echo "Build failed"
fi

program="./isa-top"

echo "Test 1: No arguments"
stdout=$($program 2> /dev/null)
stderr=$($program 2>&1 > /dev/null)
return_code=$?
if [ $return_code -eq 1 ]; then
    echo "Test 1 succeeded"
else
    echo "Test 1 failed"
fi
echo "stdout: $stdout"
echo "stderr: $stderr"

# command may not work on all systems
interface=$(ifconfig | grep -B7 "status: active" | awk '/^en/ {print $1}' | head -n 1)
interface=${interface%:}

echo "Test 2: Just interface"
stdout=$($program $interface 2> /dev/null &)
stderr=$($program $interface 2>&1 > /dev/null &)
return_code=$?
if [ $return_code -eq 0 ]; then
    echo "Test 2 succeeded"
else
    echo "Test 2 failed"
fi