import math
import socket
from select import select
import struct
import json
import pickle
import time
import random


display_width = 800
display_height = 600


def Debug(c):
    if False:
        print(str(c))


addr, port = 'localhost', 12345

packer = struct.Struct('I 3s I I')
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
server_socket.bind((addr, port))
server_socket.listen(10)
inputs = [server_socket]
clients = []


player_inputs = []
objects = []


def handle_server():
    readable, _, _ = select(inputs, [], [], 1/60)
    for s in readable:
        if s is server_socket:
            client_socket, client_address = server_socket.accept()
            Debug('new connection: ' + str(client_address))
            clients.append(client_socket)
            inputs.append(client_socket)
        else:
            data = s.recv(1024)
            if data:
                try:
                    id, cmd, x, y = packer.unpack(data)
                    update_inputs(id, cmd, x, y)
                except:
                    pass


def update_inputs(id, cmd, x, y):
    cmd = cmd.decode()
    Debug("kaptam uzenetet meghozza: " + str(cmd))
    if (cmd == 'new'):
        objects.append(player(id, x, y, 'tank.png'))
        player_inputs.append({"id": id, "key_down": {"null", "null2"}})
        Debug("uj jatekos hozzaadva")
    elif (cmd in ('KDw', 'KDs', 'KDd', 'KDa', 'KD ')):
        for i in player_inputs:
            if (i["id"] == id):
                i["key_down"].add(cmd[2])
    elif (cmd in ('KUw', 'KUs', 'KUd', 'KUa', 'KU ')):
        for i in player_inputs:
            if (i["id"] == id):
                i["key_down"].remove(cmd[2])


class player:
    def __init__(self, id, x, y, img):
        self.id = id
        self.x = x
        self.y = y
        self.angle = 0
        self.speed = 5
        self.rotation_speed = 2
        self.bullet_cd = time.time()-4

    def update(self):
        Debug("eppen updatelodom")
        Debug(player_inputs)
        for i in player_inputs:
            if i["id"] == self.id:
                key_down = i["key_down"]
                Debug("key_down: " + str(key_down))
                self.angle = self.angle % 360
                self.angle += self.rotation_speed*(('a' in key_down) -
                                                   ('d' in key_down))
                forward = (math.cos(math.radians(self.angle)),
                           -math.sin(math.radians(self.angle)))
                self.x += self.speed * \
                    forward[0]*(('w' in key_down) -
                                ('s' in key_down))
                self.y += self.speed * \
                    forward[1]*(('w' in key_down) -
                                ('s' in key_down))

                if(self.x < -20):
                    self.x = display_width+20
                elif (self.x > display_width+20):
                    self.x = -20

                if(self.y < -20):
                    self.y = display_height+20
                elif (self.y > display_height+20):
                    self.y = -20

                if (' ' in key_down and (time.time()-self.bullet_cd) > 5):
                    self.bullet_cd = time.time()
                    objects.append(
                        bullet(self.id, self.x, self.y, 'bullet.png', self.angle))


class bullet:
    def __init__(self, id, x, y, img, angle):
        self.x = x
        self.y = y
        self.angle = angle
        self.forward = (math.cos(math.radians(angle)),
                        -math.sin(math.radians(angle)))
        self.speed = 8
        self.id = id

    def update(self):
        self.x += self.speed*self.forward[0]
        self.y += self.speed*self.forward[1]
        if(self.x < -5 or self.x > display_width+5 or self.y < -5 or self.y > display_height+5):
            objects.remove(self)
        for o in objects:
            if (type(o) == player):
                if (o.id != self.id):
                    if((math.pow(o.x-self.x, 2)+math.pow(o.y-self.y, 2)) < 400):
                        o.x = int(display_width/2+random.randint(0, 400)-200)
                        o.y = int(display_height/2+random.randint(0, 400)-200)
                        objects.remove(self)


def update_game():
    for o in objects:
        o.update()
        if type(o) is player:
            Debug("player in: " + str((o.x, o.y)))


def send_gamedata():
    for ss in clients:
        data = []
        for o in objects:
            e = {"type": '', "coords": (0, 0), "angle": 2}
            if type(o) is player:
                e["type"] = 'player'
            elif type(o) is bullet:
                e["type"] = 'bullet'
            else:
                e["type"] = "unknown"
            e["coords"] = (o.x, o.y)
            e["angle"] = o.angle
            data.append(e)
        sendingdata = pickle.dumps(data)
        ss.send(sendingdata)


crashed = False
Debug('server is up and running')
while not crashed:
    handle_server()
    update_game()
    send_gamedata()
    time.sleep(1/120)

server_socket.close()


'''

szervernek elküldeni az akciókat ( mozgások és lövések) majd ő eldönti
h hova mozogtunk mi csak visszakapjuk h ki hol van egy arrayban amiben a hajók és golyók koordinátái vannak
+ még 1 szám h hanyadik a mi hajónk



'''
