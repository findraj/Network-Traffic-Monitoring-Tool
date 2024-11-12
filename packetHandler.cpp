/**
 * ISA Project 2024
 *
 * @file packetHandler.cpp
 * @brief Packet handler functions
 *
 * @author Jan Findra (xfindr01)
 */

#include "packetHandler.h"
#include <algorithm>

bool cmpBPS(pair<string, connection> a, pair<string, connection> b)
{
    return a.second.rxbps + a.second.txbps > b.second.rxbps + b.second.txbps; // sum speeds and compare
}

bool cmpPPS(pair<string, connection> a, pair<string, connection> b)
{
    return a.second.rxpps + a.second.txpps > b.second.rxpps + b.second.txpps; // sum speeds and compare
}

void computeSpeeds(map<string, connection> &connections, int period)
{
    // get the current time
    timeval now = timeval();
    gettimeofday(&now, NULL);

    auto conn = begin(connections); // iterator for the map of connections

    while (conn != end(connections)) // go through all connections
    {
        // iterators for the vectors of the connection
        auto timestamp = begin(conn->second.timestamp);
        auto rxBytes = begin(conn->second.rxBytes);
        auto txBytes = begin(conn->second.txBytes);
        auto rxPackets = begin(conn->second.rxPackets);
        auto txPackets = begin(conn->second.txPackets);

        // clear the speeds
        conn->second.rxbps = 0;
        conn->second.txbps = 0;
        conn->second.rxpps = 0;
        conn->second.txpps = 0;

        while (timestamp != end(conn->second.timestamp)) // go through all vectors, they have the same length, so we can use one iterator as condition
        {
            if (now.tv_sec - timestamp->tv_sec + (now.tv_usec - timestamp->tv_usec) / 1000000 > float(period)) // if the packet is older than the period
            {
                // remove the old data from the vectors
                timestamp = conn->second.timestamp.erase(timestamp);
                rxBytes = conn->second.rxBytes.erase(rxBytes);
                txBytes = conn->second.txBytes.erase(txBytes);
                rxPackets = conn->second.rxPackets.erase(rxPackets);
                txPackets = conn->second.txPackets.erase(txPackets);
            }
            else // if the packet is not older than the period
            {
                // add the size and number of packets to the speeds, temporary before calculating the speed
                conn->second.rxbps += *rxBytes;
                conn->second.txbps += *txBytes;
                conn->second.rxpps += *rxPackets;
                conn->second.txpps += *txPackets;
                // move the iterators to the next element
                timestamp++;
                rxBytes++;
                txBytes++;
                rxPackets++;
                txPackets++;
            }
        }

        if (conn->second.timestamp.size() == 0) // if the connection got no packets in the period
        {
            conn = connections.erase(conn); // remove the connection from the map
        }
        else
        {
            conn->second.rxbps = conn->second.rxbps * 8 / period; // calculate the speed in bits per second
            conn->second.txbps = conn->second.txbps * 8 / period; // calculate the speed in bits per second
            conn->second.rxpps = conn->second.rxpps / period;     // calculate the speed in packets per second
            conn->second.txpps = conn->second.txpps / period;     // calculate the speed in packets per second
            conn++;                                               // move the iterator to the next connection
        }
    }
}

vector<connection> sortConnections(map<string, connection> *connections, bool bytes, int period)
{
    computeSpeeds(*connections, period);
    vector<pair<string, connection>> sortedConnections; // temporary vector for sorting

    for (auto &conn : *connections) // extract the map to the vector
    {
        sortedConnections.push_back(conn);
    }

    if (bytes) // sort by bytes per second
    {
        sort(sortedConnections.begin(), sortedConnections.end(), cmpBPS);
    }
    else // sort by packets per second
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
    // create new connection
    connection newConnection = {data.ipv4, data.srcIP, data.srcPort, data.dstIP, data.dstPort, data.proto, 0, 0, 0, 0, {data.time}, {0}, {data.size}, {0}, {1}};
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
        // append all vectors with the new values (also 0s, to keep the vectors the same length)
        connections->at(keySrcToDst).timestamp.push_back(data.time);
        connections->at(keySrcToDst).rxBytes.push_back(0);
        connections->at(keySrcToDst).txBytes.push_back(data.size);
        connections->at(keySrcToDst).rxPackets.push_back(0);
        connections->at(keySrcToDst).txPackets.push_back(1);
    }
    else if (itDstToSrc != connections->end()) // if the connection already exists and it is from dst to src
    {
        // append all vectors with the new values (also 0s, to keep the vectors the same length)
        connections->at(keyDstToSrc).timestamp.push_back(data.time);
        connections->at(keyDstToSrc).rxBytes.push_back(data.size);
        connections->at(keyDstToSrc).txBytes.push_back(0);
        connections->at(keyDstToSrc).rxPackets.push_back(1);
        connections->at(keyDstToSrc).txPackets.push_back(0);
    }
    else // if the connection does not exist
    {
        newConnection(connections, data);
    }
}

void packetHandler(const struct pcap_pkthdr *pkthdr, const u_char *packet, map<string, connection> *connections)
{
    packetData data;         // structure for packet data
    data.time = pkthdr->ts;  // get the time of the packet arrival
    data.size = pkthdr->len; // get the size of the packet in bytes

    const struct ether_header *ethHeader = (const struct ether_header *)packet; // get the ethernet header

    if (ntohs(ethHeader->ether_type) == ETHERTYPE_IP) // if the ethernet type is IP(v4)
    {
        data.ipv4 = true;
        const struct ip *ipHeader = (const struct ip *)(packet + sizeof(struct ether_header));                  // get the IP header
        struct tcphdr *tcpHeader = (struct tcphdr *)(packet + sizeof(struct ether_header) + sizeof(struct ip)); // get the TCP header
        struct udphdr *udpHeader = (struct udphdr *)(packet + sizeof(struct ether_header) + sizeof(struct ip)); // get the UDP header
        char srcIP4[INET_ADDRSTRLEN];
        char dstIP4[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(ipHeader->ip_src), srcIP4, INET_ADDRSTRLEN); // get the source IP
        inet_ntop(AF_INET, &(ipHeader->ip_dst), dstIP4, INET_ADDRSTRLEN); // get the destination IP
        // convert the IPs to strings and save them to the structure
        data.srcIP = string(srcIP4);
        data.dstIP = string(dstIP4);

        switch (ipHeader->ip_p) // get the protocol
        {
        case IPPROTO_TCP:
            data.proto = "tcp";
            data.srcPort = to_string(ntohs(tcpHeader->th_sport)); // get the source port
            data.dstPort = to_string(ntohs(tcpHeader->th_dport)); // get the destination port
            break;
        case IPPROTO_UDP:
            data.proto = "udp";
            data.srcPort = to_string(ntohs(udpHeader->uh_sport)); // get the source port
            data.dstPort = to_string(ntohs(udpHeader->uh_dport)); // get the destination port
            break;
        case IPPROTO_ICMP:
            data.proto = "icmp";
            break;
        case IPPROTO_IGMP:
            data.proto = "igmp";
            break;
        default:
            data.proto = "other";
            break;
        }
    }
    else if (ntohs(ethHeader->ether_type) == ETHERTYPE_IPV6) // if the ethernet type is IP(v6)
    {
        data.ipv4 = false;
        const struct ip6_hdr *ip6Header = (const struct ip6_hdr *)(packet + sizeof(struct ether_header));            // get the IP header
        struct tcphdr *tcpHeader = (struct tcphdr *)(packet + sizeof(struct ether_header) + sizeof(struct ip6_hdr)); // get the TCP header
        struct udphdr *udpHeader = (struct udphdr *)(packet + sizeof(struct ether_header) + sizeof(struct ip6_hdr)); // get the UDP header
        char srcIP6[INET6_ADDRSTRLEN];
        char dstIP6[INET6_ADDRSTRLEN];
        inet_ntop(AF_INET6, &(ip6Header->ip6_src), srcIP6, INET6_ADDRSTRLEN); // get the source IP
        inet_ntop(AF_INET6, &(ip6Header->ip6_dst), dstIP6, INET6_ADDRSTRLEN); // get the destination IP
        // convert the IPs to strings and save them to the structure
        data.srcIP = string(srcIP6);
        data.dstIP = string(dstIP6);

        switch (ip6Header->ip6_nxt) // get the protocol
        {
        case IPPROTO_TCP:
            data.proto = "tcp";
            data.srcPort = to_string(ntohs(tcpHeader->th_sport)); // get the source port
            data.dstPort = to_string(ntohs(tcpHeader->th_dport)); // get the destination port
            break;
        case IPPROTO_UDP:
            data.proto = "udp";
            data.srcPort = to_string(ntohs(udpHeader->uh_sport)); // get the source port
            data.dstPort = to_string(ntohs(udpHeader->uh_dport)); // get the destination port
            break;
        case IPPROTO_ICMPV6:
            data.proto = "icmpv6";
            break;
        default:
            data.proto = "other";
            break;
        }
    }
    else // if the ethernet type is not IP
    {
        return;
    }

    addConnection(connections, data); // add the connection to the map
}