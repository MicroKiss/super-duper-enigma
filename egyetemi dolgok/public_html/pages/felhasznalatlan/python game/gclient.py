import pygame
import math
import socket
from select import select
import struct
import json
import random
import pickle
import sys


display_width = 800
display_height = 600


def Debug(c):
    if False:
        print(str(c))


addr, port = '172.18.37.241', 12345
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect((addr, port))
packer = struct.Struct('i 3s i i')
ID = random.randint(0, 200)

packed_data = packer.pack(
    ID, 'new'.encode(), int(display_width/2+random.randint(0, 400)-200), int(display_height/2+random.randint(0, 400)-200))
Debug("elkuldtem h new ")

key_down = {pygame.K_a, pygame.K_d}
key_down.clear()

pygame.init()
Debug("pygame.init")

gameDisplay = pygame.display.set_mode((display_width, display_height))
pygame.display.set_caption('Best game in the multiverse')

clock = pygame.time.Clock()
crashed = False
objects = []


class player:
    def __init__(self, x, y, img, angle):
        self.x = x
        self.y = y
        self.img = pygame.image.load(img)
        self.angle = angle
        self.speed = 5
        self.rotation_speed = 2

    def draw(self):
        rotated_img = pygame.transform.rotate(self.img, self.angle)
        rotRect = rotated_img.get_rect()
        rotRect.center = (self.x, self.y)
        gameDisplay.blit(rotated_img, rotRect)


class Bullet:
    def __init__(self, x, y, img, angle):
        self.x = x
        self.y = y
        self.img = pygame.image.load(img)
        self.forward = (math.cos(math.radians(angle)),
                        -math.sin(math.radians(angle)))
        self.speed = 8

    def draw(self):
        rotRect = self.img.get_rect()
        rotRect.center = (self.x, self.y)
        gameDisplay.blit(self.img, rotRect)


def update_inputs():
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            crashed = True
        if event.type == pygame.KEYDOWN:
            packed_data = packer.pack(ID, ('KD'+chr(event.key)).encode(), 0, 0)
            client_socket.send(packed_data)
        if event.type == pygame.KEYUP:
            packed_data = packer.pack(
                ID, ('KU' + chr(event.key)).encode(), 0, 0)
            client_socket.send(packed_data)
        Debug("event lekezelve")


def get_game_data():
    readable, _, _ = select([client_socket], [], [], 1/600)
    for s in readable:
        if s is client_socket:
            rawdata = s.recv(1024*64)
            if rawdata:
                data = pickle.loads(rawdata)
                Debug("kaptam gamestatet: " + str(data))
                objects.clear()
                for d in data:
                    if d["type"] == 'player':
                        objects.append(
                            player(d["coords"][0], d["coords"][1], 'tank.png', d["angle"]))
                    elif d["type"] == 'bullet':
                        objects.append(
                            Bullet(d["coords"][0], d["coords"][1], 'bullet.png', d["angle"]))


client_socket.send(packed_data)


def draw_game():
    gameDisplay.fill((200, 200, 200))
    Debug("hatter rajz")
    for o in objects:
        o.draw()
    Debug("objectek kirajzolassa utna")
    pygame.display.update()
    clock.tick(60)


while not crashed:
    update_inputs()
    get_game_data()
    Debug("get game data utani resz")
    draw_game()


pygame.quit()
quit()
