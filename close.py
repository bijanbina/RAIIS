import socket

ss = socket.socket()
ss.bind(('172.16.35.101',7778))

ss.close()
