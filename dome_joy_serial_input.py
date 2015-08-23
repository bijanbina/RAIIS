import pygame
import socket
import time
import signal
import sys

from pygame.locals import * # This module contains various constants used by Pygame

def signal_handler(signal, frame):
	ss.close()
        sys.exit(0)

def quit():
    ''' Self explanatory '''
    pygame.quit()
    sys.exit(0)
def input(events):
    ''' Function to handle events, particularly quitting the program '''
    for event in events:
        if event.type == QUIT:
            quit()
        else:
            if event.type == KEYDOWN:
                if event.key == K_ESCAPE:
                    quit()
                #else:
                #   print event.key
            else:
                #print event
		pass

signal.signal(signal.SIGINT, signal_handler)
ss = socket.socket()
ss.bind(('192.168.1.99' , 7778))
ss.listen(0)

connection, address = ss.accept()

pygame.init()
pygame.joystick.init()

joysticks = pygame.joystick.get_count()

if joysticks:
    print str(joysticks) + " joystick(s) detected!"

    for i in range(joysticks):
        joystick = pygame.joystick.Joystick(i)
        joystick.init()
        name = joystick.get_name()
        print "Joystick " + str(i) + " name: " + name

send = 0
quit = 0

stopped=1

start = 9
select = 8
triangle = 0
circle = 1
cross = 2
square = 3
up = (0,1)
down = (0,-1)
left = (-1,0)
right = (1,0)
l1 = 4
r1 = 5
l2 = 6
r2 = 7
l3 = 10
r3 = 11

dict = {}
dict[circle] = 'z'
dict[square] = 'k'
dict[triangle] = 's'
dict[cross] = 't'
dict[up] = 'u'
dict[down] = 'd'
dict[left] = 'l'
dict[right] = 'r'
dict[l1] = '['
dict[r1] = 'b'
dict[l2] = ']'
dict[r2] = 'n'
dict[l3] = 'o'
dict[r3] = 'p'

delay = 0.3

while True:
	input(pygame.event.get())
	if(joystick.get_button(start) == True):
		send = 1
		print "sending: on"
	if(joystick.get_button(select) == True):
		quit = 1
	if(send==1):
		while True:
			input(pygame.event.get())
			if(joystick.get_button(start) == True):
				send = 0
				print "sending off"
				break
			if(joystick.get_button(select) == True):
				send = 0
				quit = 1
				print "sending off"
				break
			for x in range(joystick.get_numbuttons()):
                		if ( (joystick.get_button(x) == True) and (dict.has_key(x)==True) ):
                    			connection.send(dict[x])
					time.sleep(delay)
            		hat = joystick.get_hat(0)
			if(stopped==0 and hat==(0,0)):
				stopped=1
				connection.send('t')
				time.sleep(delay)
            		if dict.has_key(hat):
                		connection.send(dict[hat])
				stopped=0
				time.sleep(delay)
	if(quit == 1):
		connection.send('.')
		break
ss.close()
