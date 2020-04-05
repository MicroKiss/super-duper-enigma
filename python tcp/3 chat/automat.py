import socket
import struct
import sys
import select
import time


tmp = 100
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect(('localhost', 12345))
while True:
    time.sleep(0.3)
    sock.send(("Micro: hacking in " + str(tmp)).encode('utf-8', 'ignore'))
    tmp = tmp-1
sock.close()
