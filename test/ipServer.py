import socket

# Server IP and Ports
SERVER_IP = '127.0.0.1'  # Localhost for testing
TCP_PORT = 12345
UDP_PORT = 12346

# TCP Server
def start_tcp_server():
    tcp_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    tcp_socket.bind((SERVER_IP, TCP_PORT))
    tcp_socket.listen(1)
    print(f"TCP Server listening on {SERVER_IP}:{TCP_PORT}")
    client_socket, address = tcp_socket.accept()
    print(f"Received TCP connection from {address}")
    client_socket.send("TCP Acknowledgment".encode())
    client_socket.close()

# UDP Server
def start_udp_server():
    udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    udp_socket.bind((SERVER_IP, UDP_PORT))
    print(f"UDP Server listening on {SERVER_IP}:{UDP_PORT}")
    data, address = udp_socket.recvfrom(1024)
    print(f"Received UDP message from {address}: {data.decode()}")
    udp_socket.sendto("UDP Acknowledgment".encode(), address)

# ICMP Server
def start_icmp_server():
    icmp_socket = socket.socket(socket.AF_INET, socket.SOCK_RAW, socket.IPPROTO_ICMP)
    icmp_socket.bind((SERVER_IP, 0))
    print("ICMP Server listening")
    data, address = icmp_socket.recvfrom(1024)
    print(f"Received ICMP message from {address}: {data}")

# ICMPv6 Server
def start_icmp6_server():
    icmp6_socket = socket.socket(socket.AF_INET6, socket.SOCK_RAW, socket.IPPROTO_ICMPV6)
    icmp6_socket.bind(('::1', 0))  # IPv6 localhost
    print("ICMPv6 Server listening")
    data, address = icmp6_socket.recvfrom(1024)
    print(f"Received ICMPv6 message from {address}: {data}")

# Start servers
if __name__ == "__main__":
    start_tcp_server()
    start_udp_server()
    start_icmp_server()
    start_icmp6_server()
