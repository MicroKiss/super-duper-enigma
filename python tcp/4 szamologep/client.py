import socket
import struct
import sys
import select


packer = struct.Struct('I 1s I')

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect(('localhost', 12345))
while True:

    szam1 = input('Add meg az 1. szamot: ')
    if szam1 == 'exit':
        break
    szam1 = int(szam1)
    op = input('Add meg az operatort: ')
    szam2 = int(input('Add meg a 2. szamot: '))

    packed_data = packer.pack(szam1, op.encode(), szam2)
    sock.send(packed_data)
    print(sock.recv(1024).decode())

sock.close()
