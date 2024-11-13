import socket
import time

# Server IP and Ports
SERVER_IP = '127.0.0.1'  # Localhost for testing
TCP_PORT = 12345
UDP_PORT = 12346

# TCP Server
def start_tcp_server():
    tcp_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    tcp_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    tcp_socket.bind((SERVER_IP, TCP_PORT))
    tcp_socket.listen(1)
    print(f"TCP Server listening on {SERVER_IP}:{TCP_PORT}")
    while True:
        client_socket, address = tcp_socket.accept()
        data = client_socket.recv(1024).decode()
        print(f"Received TCP connection from {address}")
        client_socket.send("TCP Acknowledgment".encode())
        client_socket.close()
        if data == "exit":
            break
    tcp_socket.close()

# UDP Server
def start_udp_server():
    udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    udp_socket.bind((SERVER_IP, UDP_PORT))
    print(f"UDP Server listening on {SERVER_IP}:{UDP_PORT}")
    while True:
        data, address = udp_socket.recvfrom(1024)
        udp_socket.sendto("UDP Acknowledgment".encode(), address)
        print(f"Received UDP message from {address}")
        if data.decode() == "exit":
            break
    udp_socket.close()

# ICMP Server
def start_icmp_server():
    icmp_socket = socket.socket(socket.AF_INET, socket.SOCK_RAW, socket.IPPROTO_ICMP)
    icmp_socket.bind((SERVER_IP, 0))
    print("ICMP Server listening")
    i = 0
    while True:
        data, address = icmp_socket.recvfrom(1024)
        print(f"Received ICMP message from {address}")
        i += 1
        if i > 10:
            break
    icmp_socket.close()

# ICMPv6 Server
def start_icmp6_server():
    icmp6_socket = socket.socket(socket.AF_INET6, socket.SOCK_RAW, socket.IPPROTO_ICMPV6)
    icmp6_socket.bind(('::1', 0))  # IPv6 localhost
    print("ICMPv6 Server listening")
    i = 0
    while True:
        data, address = icmp6_socket.recvfrom(1024)
        print(f"Received ICMPv6 message from {address}")
        i += 1
        if i > 10:
            break
    icmp6_socket.close()

# Start servers
if __name__ == "__main__":
    # test 1
    start_tcp_server()

    # test 2
    start_udp_server()

    # test 3
    start_icmp_server()

    # test 4
    start_icmp6_server()

    # test 5
    start_tcp_server()

    # test 6
    start_udp_server()

    # test 7
    start_icmp_server()

    # test 8
    start_icmp6_server()