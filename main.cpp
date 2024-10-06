/**
 * ISA Project 2024
 * 
 * @file main.cpp
 * @brief Main file of the project
 * 
 * @author Jan Findra (xfindr01)
 */

#include "main.h"

map<string, connection> connections; // map of connections
vector<connection> sortedConnections; // vector of 10 most active connections
args arguments;

void pHandler(u_char *userData, const struct pcap_pkthdr* pkthdr, const u_char* packet)
{
    packetHandler(pkthdr, packet, &connections); // handle the packet and update map of connections
    sortedConnections = sortConnections(&connections, arguments.bytes); // sort connections and return 10 most active
    printScreen(&sortedConnections);
    (void)userData; // suppress unused variable warning
}

int main(int argc, char *argv[])
{
    arguments = parseArgs(argc, argv);
    bpf_u_int32 net;
    bpf_u_int32 mask;
    char errbuf[PCAP_ERRBUF_SIZE]; // error buffer for pcap functions
    pcap_t *handle;

    // get network and mask of the interface
    if (pcap_lookupnet(arguments.interface.c_str(), &net, &mask, errbuf) == -1) // check if the network and mask were found
    {
        printError("Cannot find any device: " + string(errbuf), false, NULL);
    }

    handle = pcap_open_live(arguments.interface.c_str(), BUFSIZ, 1, 1000, errbuf); // open the device

    if (handle == NULL) // check if the device was opened
    {
        printError("Cannot open device: " + string(errbuf), false, NULL);
    }

    if (pcap_datalink(handle) != DLT_EN10MB) // check if the device is Ethernet
    {
        printError("Device is not Ethernet: " + string(pcap_geterr(handle)), false, NULL);
    }

    initScreen(); // initialize the screen

    // start packet capturing
    if (pcap_loop(handle, 0, pHandler, NULL) == -1) // check if the packet capturing started
    {
        printError("Cannot start packet capturing: " + string(pcap_geterr(handle)), true, NULL);
    }

    // properly close the program
    pcap_close(handle);
    closeScreen();
    return 0;
}