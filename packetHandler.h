/**
 * ISA Project 2024
 *
 * @file packetHandler.h
 * @brief Packet handler functions
 *
 * @author Jan Findra (xfindr01)
 */

#include <string>
#include <ctime>
#include <netinet/if_ether.h>
#include <netinet/ip.h>
#include <netinet/ip6.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include "messages.h"

using namespace std;

/**
 * @brief Packet data structure
 *
 * @param ipv4 True if IPv4, false if IPv6
 * @param srcIP Source IP address
 * @param srcPort Source port
 * @param dstIP Destination IP address
 * @param dstPort Destination port
 * @param proto Protocol
 * @param time Time of the packet arrival
 * @param size Size of the packet in bytes
 */
struct packetData
{
    bool ipv4;
    string srcIP;
    string srcPort;
    string dstIP;
    string dstPort;
    string proto;
    timeval time;
    int size;
};

/**
 * @brief Function to compare connections by bytes per second
 *
 * @param a First connection
 * @param b Second connection
 * @return True if a is faster than b
 */
bool cmpBPS(pair<string, connection> a, pair<string, connection> b);

/**
 * @brief Function to compare connections by packets per second
 *
 * @param a First connection
 * @param b Second connection
 * @return True if a is faster than b
 */
bool cmpPPS(pair<string, connection> a, pair<string, connection> b);

void computeSpeeds(map<string, connection> *connections, int period);

/**
 * @brief Function to sort connections and return 10 most active in vector
 *
 * @param connections Connections to sort
 * @param bytes True if sorting by bytes, false if sorting by packets
 * @param period Time between updates
 * @return Sorted connections
 */
vector<connection> sortConnections(map<string, connection> *connections, bool bytes, int period);

/**
 * @brief Function to create new connection
 *
 * @param connections Connections map
 * @param data Packet data
 */
void newConnection(map<string, connection> *connections, packetData data);

/**
 * @brief Function to add connection, create new or update existing
 *
 * @param connections Connections map
 * @param data Packet data
 */
void addConnection(map<string, connection> *connections, packetData data);

/**
 * @brief Handle loaded packets
 *
 * @param userData user data
 * @param pkthdr packet header
 * @param packet packet
 * @param connections map of connections
 */
void packetHandler(const struct pcap_pkthdr *pkthdr, const u_char *packet, map<string, connection> *connections);