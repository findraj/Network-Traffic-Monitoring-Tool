/**
 * ISA Project 2024
 *
 * @file main.cpp
 * @brief Main file of the project
 *
 * @author Jan Findra (xfindr01)
 */

#include "main.h"

map<string, connection> connections;  // map of connections
vector<connection> sortedConnections; // vector of 10 most active connections
args arguments;
pcap_t *handle;
atomic<bool> running(true);
mutex mtx;

void signalHandler(int signum)
{
    if (signum == SIGINT)
    {
        pcap_breakloop(handle); // break the packet capturing loop
        running = false;        // set the running flag to false
    }
}

void screenHandler()
{
    while (running)
    {
        auto start = chrono::high_resolution_clock::now(); // start time measuring

        {                                                                                         // scope for the lock_guard to unlock the mutex after the block
            lock_guard<mutex> lock(mtx);                                                          // lock the mutex
            sortedConnections = sortConnections(&connections, arguments.bytes, arguments.period); // sort connections and return 10 most active
        }
        printScreen(&sortedConnections);

        auto end = chrono::high_resolution_clock::now();                          // end time measuring
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start); // get the duration of the screen handling
        int sleepTime = arguments.period * 1000000 - duration.count();            // calculate the remaining time to sleep

        this_thread::sleep_for(chrono::microseconds(sleepTime)); // sleep for the remaining time
    }
}

void pHandler(u_char *userData, const struct pcap_pkthdr *pkthdr, const u_char *packet)
{
    {                                                // scope for the lock_guard to unlock the mutex after the block
        lock_guard<mutex> lock(mtx);                 // lock the mutex
        packetHandler(pkthdr, packet, &connections); // handle the packet and update map of connections
    }
    (void)userData; // suppress unused variable warning
}

int main(int argc, char *argv[])
{
    signal(SIGINT, signalHandler);
    arguments = parseArgs(argc, argv);
    bpf_u_int32 net;
    bpf_u_int32 mask;
    char errbuf[PCAP_ERRBUF_SIZE]; // error buffer for pcap functions

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
        printError("Device is not Ethernet: " + string(pcap_geterr(handle)), false, handle);
    }

    initScreen(); // initialize the screen

    thread screenThread(screenHandler); // start the screen thread

    // start packet capturing
    if (pcap_loop(handle, 0, pHandler, NULL) == -1) // check if the packet capturing started
    {
        printError("Cannot start packet capturing: " + string(pcap_geterr(handle)), true, handle);
    }

    screenThread.join(); // wait for the screen thread to finish

    // properly close the program
    pcap_close(handle);
    closeScreen();
    return 0;
}