import select
import socket


'''CLIENT aki csak hallgatózik'''


print("én csak hallgatozom")

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect(('localhost', 12346))

while True:
    readable, _, _ = select.select([sock], [], [])
    for s in readable:
        if s is sock:
            message_from_server = sock.recv(1024).decode()
            print(message_from_server)
    if(int(message_from_server) == 5):
        break

sock.close()
