/**
 * ISA Project 2024
 * 
 * @file screen.h
 * @brief Screen functions
 * 
 * @author Jan Findra (xfindr01)
 */

#include <ncurses.h>
#include <string>
#include <vector>
#include <map>

using namespace std;

/**
 * @brief Connection structure
 * 
 * @param srcIP Source IP address
 * @param srcPort Source port
 * @param dstIP Destination IP address
 * @param dstPort Destination port
 * @param proto Protocol
 * @param rxbps Received bytes per second
 * @param rxpps Received packets per second
 * @param txbps Transmitted bytes per second
 * @param txpps Transmitted packets per second
 * @param timestamp Time of the last packet
 * @param rxBytes Received bytes
 * @param txBytes Transmitted bytes
 * @param rxPackets Received packets
 * @param txPackets Transmitted packets
 */
struct connection
{
    bool ipv4;
    string srcIP;
    string srcPort;
    string dstIP;
    string dstPort;
    string proto;
    float rxbps;
    float rxpps;
    float txbps;
    float txpps;
    timeval timestamp;
    int rxBytes;
    int txBytes;
    int rxPackets;
    int txPackets;
};

/**
 * @brief Function to convert float to string and format it
 * 
 * @param number Number to convert
 * @return string Converted number
 */
string floatToString(float number);

/**
 * @brief Function to initialize the screen
 */
void initScreen();

/**
 * @brief Function to print IP and port according to the task
 * 
 * @param ipv4 True if IPv4, false if IPv6
 * @param ip IP address
 * @param port Port
 * @param row Row
 * @param col Column
 */
void printIPandPort(bool ipv4, string ip, string port, int row, int col);

/**
 * @brief Function to print header of the screen
 */
void printHeader();

/**
 * @brief Function to print line on the screen
 * 
 * @param row Row
 * @param conn Connection
 */
void printLine(int row, connection conn);

/**
 * @brief Function to print screen
 * 
 * @param connections Connections to print
 */
void printScreen(vector<connection> *connections);

/**
 * @brief Function to close the screen
 */
void closeScreen();