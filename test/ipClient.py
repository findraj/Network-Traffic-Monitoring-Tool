import socket
import time

SERVER_IP = '127.0.0.1'
TCP_PORT = 12345
UDP_PORT = 12346
TCP_PORT_2 = 12347
UDP_PORT_2 = 12348

# TCP Client
def send_tcp(message):
    tcp_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    tcp_socket.bind((SERVER_IP, TCP_PORT_2))
    tcp_socket.connect((SERVER_IP, TCP_PORT))
    tcp_socket.send(message.encode())
    response = tcp_socket.recv(1024)
    print("TCP Response:", response.decode())
    tcp_socket.close()

# UDP Client
def send_udp(message):
    udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    udp_socket.bind((SERVER_IP, UDP_PORT_2))
    udp_socket.sendto(message.encode(), (SERVER_IP, UDP_PORT))
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
    # test 1
    for i in range(20):
        send_tcp("TCP")
        time.sleep(1)
    send_tcp("exit")

    time.sleep(1)

    # test 2
    for i in range(20):
        send_udp("UDP")
        time.sleep(1)
    send_udp("exit")

    time.sleep(1)
    
    # test 3
    for i in range(20):
        send_icmp()
        time.sleep(1)

    time.sleep(1)

    # test 4
    for i in range(20):
        send_icmp6()
        time.sleep(1)