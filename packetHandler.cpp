/**
 * ISA Project 2024
 * 
 * @file packetHandler.cpp
 * @brief Packet handler functions
 * 
 * @author Jan Findra (xfindr01)
 */

#include "packetHandler.h"

bool cmp(pair<string, connection> a, pair<string, connection> b)
{
    return a.second.rxbps + a.second.txbps > b.second.lastPacket;
}

float calculateSpeed(int bytes, time_t firstPacket, time_t lastPacket)
{
    return bytes / (lastPacket - firstPacket);
}

void newConnection(map<string, connection> *connections, packetData data)
{
    int lastPacket = int(data.time);
    connection newConnection = {data.srcIP, data.srcPort, data.dstIP, data.dstPort, data.proto, 0, calculateSpeed(data.size, data.time, lastPacket), 0, calculateSpeed(1, data.time, lastPacket), int(data.time), lastPacket, 0, data.size, 0, 1};
    connections->insert(pair<string, connection>(data.srcIP + ":" + data.srcPort + "-" + data.dstIP + ":" + data.dstPort, newConnection));
}

void addConnection(map<string, connection> *connections, packetData data)
{
    string keySrcToDst = data.srcIP + ":" + data.srcPort + "-" + data.dstIP + ":" + data.dstPort;
    string keyDstToSrc = data.dstIP + ":" + data.dstPort + "-" + data.srcIP + ":" + data.srcPort;
    map<string, connection>::iterator itSrcToDst;
    map<string, connection>::iterator itDstToSrc;
    itSrcToDst = connections->find(keySrcToDst);
    itDstToSrc = connections->find(keyDstToSrc);

    if (itSrcToDst != connections->end()) // if the connection already exists and it is from src to dst
    {
        connections->at(keySrcToDst).txBytes += data.size;
        connections->at(keySrcToDst).txPackets++;
        connections->at(keySrcToDst).lastPacket = int(data.time);
    }
    else if (itDstToSrc != connections->end()) // if the connection already exists and it is from dst to src
    {
        connections->at(keyDstToSrc).rxBytes += data.size;
        connections->at(keyDstToSrc).rxPackets++;
        connections->at(keyDstToSrc).lastPacket = int(data.time);
    }
    else // if the connection does not exist
    {
        newConnection(connections, data);
    }
}

void packetHandler(const struct pcap_pkthdr* pkthdr, const u_char* packet, map<string, connection> *connections)
{
    packetData data;
    data.time = pkthdr->ts.tv_sec;

    data.size = pkthdr->len;

    const struct ether_header *eth_header = (const struct ether_header *)packet; // get the ethernet header
    const struct ip *ip_header = (const struct ip *)(packet + sizeof(struct ether_header)); // get the IP header
    struct tcphdr *tcp_header = (struct tcphdr *)(packet + sizeof(struct ether_header) + sizeof(struct ip)); // get the TCP header
    struct udphdr *udp_header = (struct udphdr *)(packet + sizeof(struct ether_header) + sizeof(struct ip)); // get the UDP header

    if (ntohs(eth_header->ether_type) == ETHERTYPE_IP) // if the ethernet type is IP(v4)
    {
        char srcIP4[INET_ADDRSTRLEN];
        char dstIP4[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(ip_header->ip_src), srcIP4, INET_ADDRSTRLEN); // get the source IP
        inet_ntop(AF_INET, &(ip_header->ip_dst), dstIP4, INET_ADDRSTRLEN); // get the destination IP
        data.srcIP = string(srcIP4);
        data.dstIP = string(dstIP4);
    }
    else if (ntohs(eth_header->ether_type) == ETHERTYPE_IPV6) // if the ethernet type is IP(v6)
    {
        char srcIP6[INET6_ADDRSTRLEN];
        char dstIP6[INET6_ADDRSTRLEN];
        inet_ntop(AF_INET6, &(ip_header->ip_src), srcIP6, INET6_ADDRSTRLEN); // get the source IP
        inet_ntop(AF_INET6, &(ip_header->ip_dst), dstIP6, INET6_ADDRSTRLEN); // get the destination IP
        data.srcIP = string(srcIP6);
        data.dstIP = string(dstIP6);
    }
    else // if the ethernet type is ARP
    {
        struct ether_arp *arp_header = (struct ether_arp *)(packet + sizeof(struct ether_header)); // get the ARP header
        char srcIP[INET_ADDRSTRLEN];
        char dstIP[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, arp_header->arp_spa, srcIP, INET_ADDRSTRLEN); // get the source IP
        inet_ntop(AF_INET, arp_header->arp_tpa, dstIP, INET_ADDRSTRLEN); // get the destination IP
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

    // test of concept
    // connection test = {data.srcIP, data.srcPort, data.dstIP, data.dstPort, data.proto, data.size, data, 0, 0};
    addConnection(connections, data);
}