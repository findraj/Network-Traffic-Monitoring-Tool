#!/bin/bash

# make

if [ $? -eq 0 ]; then
    echo -e "\e[32mBuild succeeded\e[0m"
else
    echo -e "\e[31mBuild failed\e[0m"
    exit 1
fi

program="./isa-top"

echo "Test 1: No arguments"
echo "$program"
$program
return_code=$?
if [ $return_code -eq 1 ]; then
    echo -e "\e[32mTest 1 succeeded\e[0m"
else
    echo -e "\e[31mTest 1 failed\e[0m"
fi

echo ""

echo "Test 2: Just -i"
echo "$program -i"
$program -i
return_code=$?
if [ $return_code -eq 1 ]; then
    echo -e "\e[32mTest 3 succeeded\e[0m"
else
    echo -e "\e[31mTest 3 failed\e[0m"
fi

echo ""

echo "Test 3: Just -s"
echo "$program -s"
$program -s
return_code=$?
if [ $return_code -eq 1 ]; then
    echo -e "\e[32mTest 4 succeeded\e[0m"
else
    echo -e "\e[31mTest 4 failed\e[0m"
fi

echo ""

echo "Test 4: Just -t"
echo "$program -t"
$program -t
return_code=$?
if [ $return_code -eq 1 ]; then
    echo -e "\e[32mTest 5 succeeded\e[0m"
else
    echo -e "\e[31mTest 5 failed\e[0m"
fi

echo ""

# command may not work on all systems
interface=$(ip link show | awk '/state UP/ {print $2}' | sed 's/://; q')

echo "Test 5: Just interface"
echo "$program -i $interface"
$program -i "$interface" &
pid=$!
kill -9 $pid

return_code=$?
if [ $return_code -eq 0 ]; then
    echo -e "\e[32mTest 2 succeeded\e[0m"
else
    echo -e "\e[31mTest 2 failed\e[0m"
fi

echo ""