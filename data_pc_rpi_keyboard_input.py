import socket

class _GetchUnix:
    def __init__(self):
        import tty, sys

    def __call__(self):
        import sys, tty, termios
        fd = sys.stdin.fileno()
        old_settings = termios.tcgetattr(fd)
        try:
            tty.setraw(sys.stdin.fileno())
            ch = sys.stdin.read(1)
        finally:
            termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
        return ch


getch = _GetchUnix()

ss = socket.socket()
ss.bind(('192.168.0.99' , 7778))
ss.listen(0)

connection, address = ss.accept()

send = 0
quit = 0
while True:
	c = getch()
	if(c=='1'):
		send = 1
		print "sending: on"
	if(c=='2'):
		quit = 1
	if(send==1):
		while True:
			c = getch()
			if(c=='1'):
				send = 0
				print "sending off"
				break
			if(c=='2'):
				send = 0
				quit = 1
				print "sending off"
				break
			connection.send(c)
	if(quit == 1):
		break
ss.close()

