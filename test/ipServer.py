# ISA Project 2024

# file: ipServer.py
# brief: Server for creating traffic
# author: Jan Findra (xfindr01)

import socket

SERVER_IP = '127.0.0.1'
TCP_PORT = 12345
UDP_PORT = 12346

# TCP Server
def startTcpServer():
    tcpSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    tcpSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    tcpSocket.bind((SERVER_IP, TCP_PORT))
    tcpSocket.listen(1)
    print(f"TCP Server listening on {SERVER_IP}:{TCP_PORT}")
    while True:
        clientSocket, address = tcpSocket.accept()
        data = clientSocket.recv(1024).decode()
        print(f"Received TCP connection from {address}")
        clientSocket.send("TCP Acknowledgment".encode())
        clientSocket.close()
        if data == "exit":
            break
    tcpSocket.close()

# UDP Server
def startUdpServer():
    udpSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    udpSocket.bind((SERVER_IP, UDP_PORT))
    print(f"UDP Server listening on {SERVER_IP}:{UDP_PORT}")
    while True:
        data, address = udpSocket.recvfrom(1024)
        udpSocket.sendto("UDP Acknowledgment".encode(), address)
        print(f"Received UDP message from {address}")
        if data.decode() == "exit":
            break
    udpSocket.close()

# ICMP Server
def startIcmpServer():
    icmpSocket = socket.socket(socket.AF_INET, socket.SOCK_RAW, socket.IPPROTO_ICMP)
    icmpSocket.bind((SERVER_IP, 0))
    print("ICMP Server listening")
    i = 0
    while True:
        _, address = icmpSocket.recvfrom(1024)
        print(f"Received ICMP message from {address}")
        i += 1
        if i > 10:
            break
    icmpSocket.close()

# ICMPv6 Server
def startIcmp6Server():
    icmp6Socket = socket.socket(socket.AF_INET6, socket.SOCK_RAW, socket.IPPROTO_ICMPV6)
    icmp6Socket.bind(('::1', 0))
    print("ICMPv6 Server listening")
    i = 0
    while True:
        _, address = icmp6Socket.recvfrom(1024)
        print(f"Received ICMPv6 message from {address}")
        i += 1
        if i > 10:
            break
    icmp6Socket.close()

if __name__ == "__main__":
    # test 1
    startTcpServer()

    # test 2
    startUdpServer()

    # test 3
    startIcmpServer()

    # test 4
    startIcmp6Server()

    # test 5
    startTcpServer()

    # test 6
    startUdpServer()

    # test 7
    startIcmpServer()

    # test 8
    startIcmp6Server()