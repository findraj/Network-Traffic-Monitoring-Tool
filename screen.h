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
 * @param ipv4 True if IPv4, false if IPv6
 * @param srcIP Source IP address
 * @param srcPort Source port
 * @param dstIP Destination IP address
 * @param dstPort Destination port
 * @param proto Protocol
 * @param rxbps Received bytes per second
 * @param rxpps Received packets per second
 * @param txbps Transmitted bytes per second
 * @param txpps Transmitted packets per second
 * @param timestamp Vector of timestamps
 * @param rxBytes Vector of received bytes
 * @param txBytes Vector of transmitted bytes
 * @param rxPackets Vector of received packets
 * @param txPackets Vector of transmitted packets
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
    vector<timeval> timestamp;
    vector<int> rxBytes;
    vector<int> txBytes;
    vector<int> rxPackets;
    vector<int> txPackets;
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
 * @brief Function to print IP and port properly
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