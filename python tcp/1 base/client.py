import socket

print("én vagyok a kliens")

TCP_IP = 'localhost'
TCP_PORT = 5005
BUFFER_SIZE = 1024
MESSAGE = "Megjöttem"

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((TCP_IP, TCP_PORT))


s.send(MESSAGE.encode())
data = s.recv(BUFFER_SIZE)
s.close()

print("kapott válasz :", data.decode())