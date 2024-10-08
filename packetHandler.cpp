/**
 * ISA Project 2024
 * 
 * @file packetHandler.cpp
 * @brief Packet handler functions
 * 
 * @author Jan Findra (xfindr01)
 */

#include "packetHandler.h"

bool cmpBPS(pair<string, connection> a, pair<string, connection> b)
{
    return a.second.rxbps + a.second.txbps > b.second.rxbps + b.second.txbps; // sum speeds and compare
}

bool cmpPPS(pair<string, connection> a, pair<string, connection> b)
{
    return a.second.rxpps + a.second.txpps > b.second.rxpps + b.second.txpps; // sum speeds and compare
}

void refreshSpeeds(map<string, connection> &connections)
{
    // get the current time
    timeval now = timeval();
    gettimeofday(&now, NULL);

    for (auto &conn : connections) // go through all connections and calculate the new speeds
    {
        if (conn.second.timestamp.tv_sec - now.tv_sec + (conn.second.timestamp.tv_usec - now.tv_usec) / 1000000.0 > 1.0) // if the last packet was more than 1 second ago
        {
            connections.erase(conn.first); // remove the connection
        }
        else
        {
            conn.second.rxbps = conn.second.rxBytes;
            conn.second.rxpps = conn.second.rxPackets;
            conn.second.txbps = conn.second.txBytes;
            conn.second.txpps = conn.second.txPackets;
        }
    }
}

vector<connection> sortConnections(map<string, connection> *connections, bool bytes)
{
    refreshSpeeds(*connections); // refresh the speeds
    vector<pair<string, connection>> sortedConnections; // temporary vector for sorting

    for (auto &conn : *connections) // extract the map to the vector
    {
        sortedConnections.push_back(conn);
    }

    if (bytes) // sort by bytes
    {
        sort(sortedConnections.begin(), sortedConnections.end(), cmpBPS);
    }
    else // sort by packets
    {
        sort(sortedConnections.begin(), sortedConnections.end(), cmpPPS);
    }

    vector<connection> sortedConnectionsVector; // vector of 10 most active connections

    for (auto &conn : sortedConnections) // extract the 10 most active connections
    {
        sortedConnectionsVector.push_back(conn.second);
    }

    return sortedConnectionsVector;
}

void newConnection(map<string, connection> *connections, packetData data)
{
    // get the current time
    timeval now = timeval();
    gettimeofday(&now, NULL);
    connection newConnection = {data.ipv4, data.srcIP, data.srcPort, data.dstIP, data.dstPort, data.proto, 0, 0, 0, 0, data.time, 0, data.size, 0, 1}; // create new connection
    // insert the new connection to the map, key is made from source and destination IP and port
    connections->insert(pair<string, connection>(data.srcIP + ":" + data.srcPort + "-" + data.dstIP + ":" + data.dstPort, newConnection));
}

void addConnection(map<string, connection> *connections, packetData data)
{
    // create two keys for the map to check if the connection already exists even if the source and destination are switched
    string keySrcToDst = data.srcIP + ":" + data.srcPort + "-" + data.dstIP + ":" + data.dstPort; // key from source to destination
    string keyDstToSrc = data.dstIP + ":" + data.dstPort + "-" + data.srcIP + ":" + data.srcPort; // key from destination to source
    // two iterators for the map
    map<string, connection>::iterator itSrcToDst;
    map<string, connection>::iterator itDstToSrc;
    // find the connection in the map
    itSrcToDst = connections->find(keySrcToDst);
    itDstToSrc = connections->find(keyDstToSrc);

    if (itSrcToDst != connections->end()) // if the connection already exists and it is from src to dst
    {
        connections->at(keySrcToDst).txBytes += data.size;
        connections->at(keySrcToDst).txPackets++;
    }
    else if (itDstToSrc != connections->end()) // if the connection already exists and it is from dst to src
    {
        connections->at(keyDstToSrc).rxBytes += data.size;
        connections->at(keyDstToSrc).rxPackets++;
    }
    else // if the connection does not exist
    {
        newConnection(connections, data);
    }
}

void packetHandler(const struct pcap_pkthdr* pkthdr, const u_char* packet, map<string, connection> *connections)
{
    packetData data; // structure for packet data
    data.time = pkthdr->ts; // get the time of the packet
    data.size = pkthdr->len; // get the size of the packet in bytes

    const struct ether_header *eth_header = (const struct ether_header *)packet; // get the ethernet header
    const struct ip *ip_header = (const struct ip *)(packet + sizeof(struct ether_header)); // get the IP header
    struct tcphdr *tcp_header = (struct tcphdr *)(packet + sizeof(struct ether_header) + sizeof(struct ip)); // get the TCP header
    struct udphdr *udp_header = (struct udphdr *)(packet + sizeof(struct ether_header) + sizeof(struct ip)); // get the UDP header

    if (ntohs(eth_header->ether_type) == ETHERTYPE_IP) // if the ethernet type is IP(v4)
    {
        data.ipv4 = true;
        char srcIP4[INET_ADDRSTRLEN];
        char dstIP4[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(ip_header->ip_src), srcIP4, INET_ADDRSTRLEN); // get the source IP
        inet_ntop(AF_INET, &(ip_header->ip_dst), dstIP4, INET_ADDRSTRLEN); // get the destination IP
        // convert the IPs to strings and save them to the structure
        data.srcIP = string(srcIP4);
        data.dstIP = string(dstIP4);
    }
    else if (ntohs(eth_header->ether_type) == ETHERTYPE_IPV6) // if the ethernet type is IP(v6)
    {
        data.ipv4 = false;
        char srcIP6[INET6_ADDRSTRLEN];
        char dstIP6[INET6_ADDRSTRLEN];
        inet_ntop(AF_INET6, &(ip_header->ip_src), srcIP6, INET6_ADDRSTRLEN); // get the source IP
        inet_ntop(AF_INET6, &(ip_header->ip_dst), dstIP6, INET6_ADDRSTRLEN); // get the destination IP
        // convert the IPs to strings and save them to the structure
        data.srcIP = string(srcIP6);
        data.dstIP = string(dstIP6);
    }
    else // if the ethernet type is ARP
    {
        data.ipv4 = true;
        struct ether_arp *arp_header = (struct ether_arp *)(packet + sizeof(struct ether_header)); // get the ARP header
        char srcIP[INET_ADDRSTRLEN];
        char dstIP[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, arp_header->arp_spa, srcIP, INET_ADDRSTRLEN); // get the source IP
        inet_ntop(AF_INET, arp_header->arp_tpa, dstIP, INET_ADDRSTRLEN); // get the destination IP
        // convert the IPs to strings and save them to the structure
        data.srcIP = string(srcIP);
        data.dstIP = string(dstIP);
    }

    switch (ip_header->ip_p) // get the protocol
    {
        case IPPROTO_ICMP:
            data.proto = "icmp";
            break;
        case IPPROTO_ICMPV6:
            data.proto = "icmpv6";
            break;
        case IPPROTO_IGMP:
            data.proto = "igmp";
            break;
        case IPPROTO_TCP:
            data.proto = "tcp";
            data.srcPort = to_string(ntohs(tcp_header->th_sport)); // get the source port
            data.dstPort = to_string(ntohs(tcp_header->th_dport)); // get the destination port 
            break;
        case IPPROTO_UDP:
            data.proto = "udp";
            data.srcPort = to_string(ntohs(udp_header->uh_sport)); // get the source port
            data.dstPort = to_string(ntohs(udp_header->uh_dport)); // get the destination port
            break;
        default:
            data.proto = "other";
            break;
    }

    addConnection(connections, data); // add the connection to the map
}