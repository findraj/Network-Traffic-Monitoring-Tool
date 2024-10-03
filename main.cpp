/**
 * ISA Project 2024
 * 
 * @file main.cpp
 * @brief Main file of the project
 * 
 * @author Jan Findra (xfindr01)
 */

#include "main.h"

int main(int argc, char *argv[]) {
    args arguments = parseArgs(argc, argv);
    bpf_u_int32 net;
    bpf_u_int32 mask;
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle;

    if (pcap_lookupnet(arguments.interface.c_str(), &net, &mask, errbuf) == -1) {
        printError("Cannot find any device: " + string(errbuf));
    }

    handle = pcap_open_live(arguments.interface.c_str(), BUFSIZ, 1, 1000, errbuf);
    if (handle == NULL) {
        printError("Cannot open device: " + string(errbuf));
    }

    if (pcap_datalink(handle) != DLT_EN10MB) {
        printError("Device is not Ethernet: " + string(pcap_geterr(handle)));
    }

    initScreen();

    if (pcap_loop(handle, 0, packetHandler, NULL) == -1) {
        printError("Cannot start packet capturing: " + string(pcap_geterr(handle)));
    }

    closeScreen();
    return 0;
}