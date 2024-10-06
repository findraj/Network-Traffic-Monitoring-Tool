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
 * @param rxbps Received bits per second
 * @param rxpps Received packets per second
 * @param txbps Transmitted bits per second
 * @param txpps Transmitted packets per second
 * @param firstPacket Time of the first packet
 * @param lastPacket Time of the last packet
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
    timeval first;
    timeval last;
    int rxBytes;
    int txBytes;
    int rxPackets;
    int txPackets;
};

string floatToString(float number);

void initScreen();

void printIPandPort(bool ipv4, string ip, string port, int row, int col);

void printHeader();

void printLine(int row, connection conn);

void printScreen(vector<connection> *connections);

void closeScreen();