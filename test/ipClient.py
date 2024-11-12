import socket

SERVER_IP = '127.0.0.1'
TCP_PORT = 12345
UDP_PORT = 12346

# TCP Client
def send_tcp():
    tcp_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    tcp_socket.connect((SERVER_IP, TCP_PORT))
    tcp_socket.send("Hello from TCP Client!".encode())
    response = tcp_socket.recv(1024)
    print("TCP Response:", response.decode())
    tcp_socket.close()

# UDP Client
def send_udp():
    udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    udp_socket.sendto("Hello from UDP Client!".encode(), (SERVER_IP, UDP_PORT))
    response, _ = udp_socket.recvfrom(1024)
    print("UDP Response:", response.decode())

# ICMP Client
def send_icmp():
    icmp_socket = socket.socket(socket.AF_INET, socket.SOCK_RAW, socket.IPPROTO_ICMP)
    icmp_packet = b'\x08\x00\xf7\xff' + b'\x00' * 60  # Simple echo request
    icmp_socket.sendto(icmp_packet, (SERVER_IP, 0))
    print("ICMP Message Sent")

# ICMPv6 Client
def send_icmp6():
    icmp6_socket = socket.socket(socket.AF_INET6, socket.SOCK_RAW, socket.IPPROTO_ICMPV6)
    icmp6_packet = b'\x80\x00\xf7\xff' + b'\x00' * 60  # Simple ICMPv6 echo request
    icmp6_socket.sendto(icmp6_packet, ('::1', 0))  # IPv6 localhost
    print("ICMPv6 Message Sent")

# Run Clients
if __name__ == "__main__":
    send_tcp()
    send_udp()
    send_icmp()
    send_icmp6()
