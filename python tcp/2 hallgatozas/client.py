import socket
import select


'''CLIENT'''
print("én vagyok a kliens")


number = 1


sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect(('localhost', 12346))

while True:
    readable, _, _ = select.select([sock], [], [], 1)
    for s in readable:
        if s is sock:
            print(sock.recv(1024).decode())

    sock.send(str(number).encode())
    number += 1
sock.close()
