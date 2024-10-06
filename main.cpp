/**
 * ISA Project 2024
 * 
 * @file main.cpp
 * @brief Main file of the project
 * 
 * @author Jan Findra (xfindr01)
 */

#include "main.h"

map<string, connection> connections;
vector<connection> sortedConnections;
args arguments;

void pHandler(u_char *userData, const struct pcap_pkthdr* pkthdr, const u_char* packet){
    packetHandler(pkthdr, packet, &connections);
    sortedConnections = sortConnections(&connections, arguments.bytes);
    printScreen(&sortedConnections);
}

int main(int argc, char *argv[]) {
    arguments = parseArgs(argc, argv);
    bpf_u_int32 net;
    bpf_u_int32 mask;
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle;

    if (pcap_lookupnet(arguments.interface.c_str(), &net, &mask, errbuf) == -1) {
        printError("Cannot find any device: " + string(errbuf), false, NULL);
    }

    handle = pcap_open_live(arguments.interface.c_str(), BUFSIZ, 1, 1000, errbuf);
    if (handle == NULL) {
        printError("Cannot open device: " + string(errbuf), false, NULL);
    }

    if (pcap_datalink(handle) != DLT_EN10MB) {
        printError("Device is not Ethernet: " + string(pcap_geterr(handle)), false, NULL);
    }

    initScreen();

    while(true)
    {
        if (pcap_dispatch(handle, 0, pHandler, NULL) == -1) {
            printError("Cannot start packet capturing: " + string(pcap_geterr(handle)), true, NULL
            );
        }
    }
    pcap_close(handle);
    closeScreen();
    return 0;
}