import socket

'''
Kávéfőző "szerver" objektum orientáltan :D
'''
coffe_port = ('localhost', 12345)


def Debug(msg):
    if True:
        print(msg)


class Bartender:
    def __init__(self, ip, port):
        # sajat socketjének létrehozása ( ezen várja a neki jövő dolgokat)
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.socket.bind((ip, port))
        # ennek segítségével fog kommunikálni a kávéfőzővel
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        Debug("Bartender létrehozva")

    def __del__(self):
        self.socket.close()
        Debug("Bartender kitörölve")

    def handle(self, msg):
        answer = ""
        if (msg == "Tea"):
            answer = "Enjoy your: Tea"
        else:
            self.sock.sendto(msg.encode(), coffe_port)
            answer = self.sock.recvfrom(1024)[0].decode()

        return answer

    def run(self):
        while True:
            packed_data, addr = self.socket.recvfrom(1024)
            answer = self.handle(packed_data.decode())
            self.socket.sendto(answer.encode(), addr)


bart = Bartender('localhost', 12344)
bart.run()
del bart
