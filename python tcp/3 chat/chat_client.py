import socket
import struct
import sys
import select

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect(('localhost', 12345))
while True:
    readable, _, _ = select.select([sock, sys.stdin], [], [])
    for s in readable:
        if s == sys.stdin:
            sock.send(("Micro: " + sys.stdin.readline()
                       ).encode('utf-8', 'ignore'))
        else:
            print(sock.recv(1024).decode('utf-8'))
sock.close()


'''
        szam1 = input('Add meg az 1. szamot: ')
        if szam1 =='exit':
            break
        szam1 = int(szam1)
        op = input('Add meg az operatort: ')
        szam2 = int(input('Add meg a 2. szamot: '))

        packer = struct.Struct('I 1s I')
        packed_data = packer.pack(szam1, op.encode(), szam2)
        sock.send(packed_data)
        print(sock.recv(1024).decode())
'''
