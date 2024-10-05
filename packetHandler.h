/**
 * ISA Project 2024
 * 
 * @file packetHandler.h
 * @brief Packet handler functions
 * 
 * @author Jan Findra (xfindr01)
 */

#include <pcap.h>
#include <string>
#include <ctime>
#include <netinet/if_ether.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include "screen.h"

using namespace std;

struct packetData
{
    string srcIP;
    string srcPort;
    string dstIP;
    string dstPort;
    string proto;
    time_t time;
    int size;
};

bool cmp(pair<string, connection> a, pair<string, connection> b);

vector<connection> sortConnections(map<string, connection> *connections);

float calculateSpeed(int number, time_t firstPacket, time_t lastPacket);

void newConnection(map<string, connection> *connections, packetData data);

void addConnection(map<string, connection> *connections, packetData data);

/**
 * @brief Handle loaded packets
 * 
 * @param userData user data
 * @param pkthdr packet header
 * @param packet packet
 */
void packetHandler(const struct pcap_pkthdr* pkthdr, const u_char* packet, map<string, connection> *connections);