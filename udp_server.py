#******************************************************************************
# File Name:   udp_server.py
#
# Description: A simple "udp server" for demonstrating UDP usage.
# The server sends LED ON/OFF commands to the connected UDP client
# and receives acknowledgement from the client.
#
#********************************************************************************
# $ Copyright 2021-2023 Cypress Semiconductor $.
#********************************************************************************

#!/usr/bin/python

import socket
import optparse
import time
import sys

DEFAULT_IP   = socket.gethostbyname(socket.gethostname())   # IP address of the UDP server
DEFAULT_PORT = 50007             # Port of the UDP server

LED_ON = '1'
LED_OFF = '0'

def enter_command(sock, addr):
    print("============================================================")
    cmd = int(input('Enter 0 to turn off or 1 to turn on the LED on Client\nInput Command: '))
    if cmd == 1:
        sock.sendto(bytes(LED_ON, "utf-8"), addr)
    elif cmd == 0:
        sock.sendto(bytes(LED_OFF, "utf-8"), addr)
    else:
        sock.sendto(bytes(str(cmd), "utf-8"), addr)

def echo_server(host, port):
    print("============================================================")
    print("UDP Server")
    print("============================================================")
    # Create a UDP socket
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    #Bind UDP Server
    sock.bind((host,port))
    print('UDP Server on IP Address: {} port {}'.format(host, port))
    print('waiting to receive message from UDP Client')
    
    while True:
        data, addr = sock.recvfrom(4096)
        if data == bytes('A', "utf-8"):
            print('Ready to send command to client')
            enter_command(sock, addr)
        elif data == bytes('LED ON ACK', "utf-8"):
            print("LED ON Acknowledgement received")
            enter_command(sock, addr)
        elif data == bytes('LED OFF ACK', "utf-8"):
            print("LED OFF Acknowledgement received")
            enter_command(sock, addr)
        else:
            print("Message from Client: {}".format(data))
            enter_command(sock, addr)
        

if __name__ == '__main__':
    parser = optparse.OptionParser()
    parser.add_option("-p", "--port", dest="port", type="int", default=DEFAULT_PORT, help="Port to listen on [default: %default].")
    parser.add_option("--hostname", dest="hostname", default=DEFAULT_IP, help="Hostname to listen on.")

    (options, args) = parser.parse_args()

    echo_server(options.hostname, options.port)
