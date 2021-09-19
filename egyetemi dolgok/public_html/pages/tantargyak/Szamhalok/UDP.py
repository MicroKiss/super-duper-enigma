import socket
import struct

'''
UDP SERVER
'''

serv_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
serv_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
serv_sock.bind(('localhost', 12345))
while True:
    packed_data, addr = serv_sock.recvfrom(1024)
    packer = struct.Struct('I 1s I')
    (szam1, op, szam2) = packer.unpack(packed_data)
    serv_sock.sendto("megkaptam koszi".encode(), addr)
serv_sock.close()


'''
UDP CLIENT
'''


sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
szam1 = int(input('Add meg az 1. szamot'))
op = input('Add meg az operatort')
szam2 = int(input('Add meg a 2. szamot'))

packer = struct.Struct('I 1s I')
packed_data = packer.pack(szam1, op.encode(), szam2)
sock.sendto(packed_data, ('localhost', 12345))
print(sock.recvfrom(1024)[0])
sock.close()
