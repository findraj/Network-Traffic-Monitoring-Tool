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
#include "screen.h"

using namespace std;

struct packet
{
    string srcIP;
    string srcPort;
    string dstIP;
    string dstPort;
    string proto;
    int size;
};

/**
 * @brief Handle loaded packets
 * 
 * @param userData user data
 * @param pkthdr packet header
 * @param packet packet
 */
void packetHandler(u_char *userData, const struct pcap_pkthdr* pkthdr, const u_char* packet);