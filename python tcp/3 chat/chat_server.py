import socket
import select

serv_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
serv_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
serv_sock.bind(('localhost', 12345))
serv_sock.listen(100)
inputs = [serv_sock]
clients = []

while True:
    readable, _, _ = select.select(inputs, [], [])
    for s in readable:
        if s is serv_sock:
            cli_sock, cli_addr = serv_sock.accept()
            print("Uj kliens: " + str(cli_addr))
            inputs.append(cli_sock)
            clients.append(cli_sock)
        else:
            data = s.recv(1024)
            if data:
                for ss in clients:
                    if ss != s:
                        ss.send(data)
            else:
                s.close()
                inputs.remove(s)
                clients.remove(s)
serv_sock.close()
