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

/**
 * @brief Handle loaded packets
 * 
 * @param userData user data
 * @param pkthdr packet header
 * @param packet packet
 */
void packetHandler(const struct pcap_pkthdr* pkthdr, const u_char* packet, vector<connection> &connections);