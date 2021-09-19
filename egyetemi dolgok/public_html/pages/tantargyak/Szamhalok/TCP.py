import socket
import select
import sys

'''
SERVER
'''
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
sock.bind(('localhost', 12346))
sock.listen(10)
inputs = [sock]
clients = []
while True:
    readable, _, _ = select.select(inputs, [], [])
    for s in readable:
        if s is sock:
            new_cient, cli_addr = s.accept()
            print('Uj kliens kapcsolodott: ' + str(cli_addr))
            inputs.append(new_cient)
            clients.append(new_cient)
        else:
            client_message = s.recv(1024)
            if client_message:
                print(client_message.decode())
                for c in clients:
                    if c is not s:
                        c.send(client_message)
            else:
                inputs.remove(s)
                clients.remove(s)
sock.close()


'''
CLIENT

'''

number = 1

name = "Micro"
if (len(sys.argv) > 1):
    name = sys.argv[1]


sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect(('localhost', 12346))
while True:
    readable, _, _ = select.select([sock], [], [], 0.1)
    for s in readable:
        if s is sock:
            print(sock.recv(1024).decode())

    sock.send(str(number).encode())
    number += 1
sock.close()
