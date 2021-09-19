import socket

'''
UDP CLIENT
'''

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)


while True:
    msg = input('Add meg a parancsot:')
    print("")
    sock.sendto(msg.encode(), ('localhost', 12345))
    print(sock.recvfrom(1024)[0].decode())
sock.close()
