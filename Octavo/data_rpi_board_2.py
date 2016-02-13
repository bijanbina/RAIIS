import socket
import serial
import time
import signal
import sys
import thread

#Send data via serial port (received from wireless) and receive dara from serial (Multithread)

port = serial.Serial('/dev/ttyUSB0', baudrate = 38400, parity='E', timeout = 1)
ss = socket.socket()
ss.connect(('192.168.1.100' , 7778))

quit = 0
control = 0

def signal_handler(signal, frame):
	port.close()
	ss.close()
        sys.exit(0)

def Send_Data(control_id):
	global control
	global quit
	global port
	global ss

	while True:
		c = ss.recv(1)
		if(c=='.'):
			quit = 1
		if quit==1:
			break
		while control!=0:
			pass
		control = control_id
		print "recieved ", c
		control = 0
		port.write(c)

def Receive_Data(control_id):
	global control
	global quit
	global port

	while True:
		time.sleep(0.5)
		port.flushInput()
		serial_read = port.readline()
		if len(serial_read)!=0:
			while control!=0:
				pass
			control = control_id
			print serial_read
			log=serial_read.split(",")
			if len(log)==3:
				log_file=open("/srv/http/stat.json","w")
				log_file.write("{\"mode\":")
				log_file.write(log[0])
				log_file.write(",\"angle\":")
				log_file.write(log[1])
				log_file.write(",\"brush\":")
				log_file.write(log[2])
				log_file.write("}")	
			control = 0	
		if quit==1:
			break

signal.signal(signal.SIGINT, signal_handler)
thread.start_new_thread(Send_Data, (1,))
thread.start_new_thread(Receive_Data, (2,))

while True:
	if quit==1:
		port.close()
		ss.close()
		sys.exit(0)
