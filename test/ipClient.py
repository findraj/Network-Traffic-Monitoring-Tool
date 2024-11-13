# ISA Project 2024

# file: ipClient.py
# brief: Client for creating traffic
# author: Jan Findra (xfindr01)

import socket
import time

SERVER_IP = '127.0.0.1'
TCP_PORT = 12345
UDP_PORT = 12346
TCP_PORT_2 = 12347
UDP_PORT_2 = 12348

# TCP Client
def sendTcp(message):
    tcpSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    tcpSocket.bind((SERVER_IP, TCP_PORT_2))
    tcpSocket.connect((SERVER_IP, TCP_PORT))
    tcpSocket.send(message.encode())
    response = tcpSocket.recv(1024)
    print("TCP Response:", response.decode())
    tcpSocket.close()

# UDP Client
def sendUdp(message):
    udpSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    udpSocket.bind((SERVER_IP, UDP_PORT_2))
    udpSocket.sendto(message.encode(), (SERVER_IP, UDP_PORT))
    response, _ = udpSocket.recvfrom(1024)
    print("UDP Response:", response.decode())
    udpSocket.close()

# ICMP Client
def sendIcmp():
    icmpSocket = socket.socket(socket.AF_INET, socket.SOCK_RAW, socket.IPPROTO_ICMP)
    icmpPacket = b'\x08\x00\xf7\xff' + b'\x00' * 60  # simple echo request
    icmpSocket.sendto(icmpPacket, (SERVER_IP, 0))
    print("ICMP Message Sent")
    icmpSocket.close()

# ICMPv6 Client
def sendIcmp6():
    icmp6Socket = socket.socket(socket.AF_INET6, socket.SOCK_RAW, socket.IPPROTO_ICMPV6)
    icmp6Packet = b'\x80\x00\xf7\xff' + b'\x00' * 60 # simple ICMPv6 echo request
    icmp6Socket.sendto(icmp6Packet, ('::1', 0))
    print("ICMPv6 Message Sent")
    icmp6Socket.close()

if __name__ == "__main__":
    # test 1
    for i in range(10):
        sendTcp("TCP")
        time.sleep(1)
    sendTcp("exit")

    time.sleep(1)

    # test 2
    for i in range(10):
        sendUdp("UDP")
        time.sleep(1)
    sendUdp("exit")

    time.sleep(1)
    
    # test 3
    for i in range(10):
        sendIcmp()
        time.sleep(1)

    time.sleep(1)

    # test 4
    for i in range(10):
        sendIcmp6()
        time.sleep(1)

    time.sleep(1)

    # test 5
    for i in range(10):
        sendTcp("TCP")
        time.sleep(0.5)
    sendTcp("exit")

    time.sleep(1)

    # test 6
    for i in range(10):
        sendUdp("UDP")
        time.sleep(0.5)
    sendUdp("exit")

    time.sleep(1)

    # test 7
    for i in range(10):
        sendIcmp()
        time.sleep(0.5)

    time.sleep(1)

    # test 8
    for i in range(10):
        sendIcmp6()
        time.sleep(0.5)
    