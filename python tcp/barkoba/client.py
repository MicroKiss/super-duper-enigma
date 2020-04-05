import socket
import struct
import time
from select import select
from sys import argv
from random import randrange
import math


def debug(message):
    if(True):
        print(message)


POWER = True
op = '<'
packer = struct.Struct('1s I')
# addr, port = argv[1], int(argv[2])
addr, port = 'localhost', 12345
minValue = 1
maxValue = 100
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect((addr, port))


def guess(min, max, op):
    debug(str(min) + ' ' + str(max))
    if(min == max):
        debug('probalkozom: =' + str(min))
        packed_data = packer.pack(
            '='.encode(), min)
        client_socket.send(packed_data)
    else:
        debug('probalkozom: '+op+' ' + str(math.floor((min+max)/2)))
        packed_data = packer.pack(
            op.encode(), math.floor((min+max)/2))
        client_socket.send(packed_data)


def handle_answer(minValue, maxValue):
    server_answer, _ = packer.unpack(client_socket.recv(1024))
    server_answer = server_answer.decode()
    debug('azt mondta a szerver h. : ' + server_answer)
    # Y = kitaláltamm V = más kitalálta K = kiestem mert rosszra tippeltem
    if(server_answer == 'Y' or server_answer == 'V' or server_answer == 'K'):
        return 0, 0, True
    if (op == '<'):
        if (server_answer == 'I'):
            maxValue = math.floor((maxValue+minValue)/2)-1
        else:
            minValue = math.floor((maxValue+minValue)/2)
    elif (op == '>'):
        if (server_answer == 'N'):
            maxValue = math.floor((maxValue+minValue)/2)
        else:
            minValue = math.floor((maxValue+minValue)/2)+1
    return minValue, maxValue, False


while POWER:
    debug('most fogok aludni')
    time.sleep(1)
    guess(minValue, maxValue, op)
    minValue, maxValue, OVER = handle_answer(minValue, maxValue)
    if (OVER):
        POWER = False
    if(op == '<'):
        op = '>'
    else:
        op = '<'
