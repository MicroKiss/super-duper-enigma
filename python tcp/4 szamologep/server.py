import socket
import struct
import select


def calc(szam1, op, szam2):
    if op == '+':
        return szam1+szam2
    elif op == '-':
        return szam1-szam2
    elif op == '/':
        return szam1/szam2
    elif op == '*':
        return szam1*szam2
    else:
        return 'Nem megfelelo operator!\n'


packer = struct.Struct('I 1s I')

serv_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
serv_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
serv_sock.bind(('localhost', 12345))
serv_sock.listen(10)
inputs = [serv_sock]
while True:
    readable, _, _ = select.select(inputs, [], [])
    for s in readable:
        if s is serv_sock:
            cli_sock, cli_addr = serv_sock.accept()
            print("Uj kliens: " + str(cli_addr))
            inputs.append(cli_sock)
        else:
            packed_data = s.recv(1024)
            if packed_data:

                (szam1, op, szam2) = packer.unpack(packed_data)
                s.send(str(calc(szam1, op.decode(), szam2)).encode())
            else:
                print("byeeee")
                s.close()
                inputs.remove(s)
serv_sock.close()
