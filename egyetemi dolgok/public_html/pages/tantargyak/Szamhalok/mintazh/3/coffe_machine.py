import socket

'''
Kávéfőző "szerver" objektum orientáltan :D
'''


def Debug(msg):
    if True:
        print(msg)


class Coffe_machine:
    def __init__(self, ip, port):
        self.status = "off"
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.socket.bind((ip, port))
        Debug("kávéfőző létrehozva itt: " + ip + " " + str(port))

    def __del__(self):
        self.socket.close()
        Debug("kávéfőző kitörölve")

    def handle(self, msg):
        answer = ""
        if (msg == "Power"):
            self.status = "off" if self.status == "on" else "on"
            # bar ide lehet nem kell a "Powered on" válasz de sztem ugy logikusabb
            answer = "Powered off" if self.status == "off" else "Powered on"
        else:
            if (self.status == "off"):
                answer = "Powered off"
            else:
                if (msg in ["Espresso", "Cappuccino"]):
                    answer = "Enjoy your: " + msg
                else:
                    answer = "I do not know what is: " + msg

        return answer

    def run(self):
        Debug("tökre mukodom")
        while True:
            packed_data, addr = self.socket.recvfrom(1024)
            answer = self.handle(packed_data.decode())
            self.socket.sendto(answer.encode(), addr)


machine = Coffe_machine('localhost', 12345)
machine.run()
del machine
