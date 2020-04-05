import socket
import time
import struct
from select import select
from sys import argv
from random import randrange


def debug(message):
    if(True):
        print(message)


solution = randrange(100)+1

debug('solution: ' + str(solution))


def check_prediction(op, num):
    if (op == '<'):
        return ('I' if solution < num else 'N')
    if (op == '>'):
        return ('I' if solution > num else 'N')
    if (op == '='):
        return ('Y' if solution == num else 'K')
    # ide johetne hibakezelesW


# addr, port = argv[1], int(argv[2])
addr, port = 'localhost', 12345

packer = struct.Struct('1s I')
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
server_socket.bind((addr, port))
server_socket.listen(10)
inputs = [server_socket]
clients = []
while True:
    readable, _, _ = select(inputs, [], [])
    for s in readable:
        if s is server_socket:
            client_socket, client_address = server_socket.accept()
            debug('uj kliens' + str(client_address))
            clients.append(client_socket)
            inputs.append(client_socket)
        else:
            data = s.recv(1024)
            if data:
                op, num = packer.unpack(data)
                result = check_prediction(op.decode(), num)
                s.send(packer.pack(result.encode(), 0))
                if (result == 'Y'):       # mindenkinek elkuldjuk a vege szot
                    inputs.remove(s)
                    clients.remove(s)
                    for ss in clients:
                        ss.send(packer.pack('V'.encode(), 0))
                        inputs.remove(ss)
                        clients.remove(ss)
                    debug('haza kuldtem mindenkit')
                    time.sleep(1)
                    solution = randrange(100)+1
                    debug('uj szam =' + str(solution))

server_socket.close()
