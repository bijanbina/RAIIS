import socket
import serial
import time
import signal
import sys
import thread

#Send data via serial port (received from wireless) and receive dara from serial (Multithread)

port = serial.Serial('/dev/ttyUSB0', baudrate = 38400, parity='E', timeout = 1)
ss = socket.socket()
ss.connect(('192.168.1.99' , 7778))

quit = 0
print_control = 0
serial_write_control = 0
dog = 0
watch_time = 2
log_file=open("/var/www/stat.json","w")

def signal_handler(signal, frame):
	port.close()
	ss.close()
        sys.exit(0)

def Send_Data(control_id):
	global print_control
	global quit
	global port
	global ss
	global serial_write_control

	while True:
		c = ss.recv(1)
		if(c=='.'):
			quit = 1
		if quit==1:
			break
		while print_control!=0:
			pass
		print_control = control_id
		print "recieved ", c
		print_control = 0
		while serial_write_control!=0:
			pass
		serial_write_control = control_id
		port.write(c)
		serial_write_control = 0

def Receive_Data(control_id):
	global print_control
	global quit
	global port
	global log_file	

	while True:
		time.sleep(0.5)
		port.flushInput()
		serial_read = port.readline()
		if len(serial_read)!=0:
			while print_control!=0:
				pass
			print_control = control_id
			print serial_read
			print_control = 0	
			log=serial_read.split(",")
			if len(log)==3:
				log_file.write("{\"mode\":")
				log_file.write(log[0])
				log_file.write(",\"angle\":")
				log_file.write(log[1])
				log_file.write(",\"brush\":")
				log_file.write(log[2])
				log_file.write("}")	
			else:
				log_file.write("{\"mode\":")
				log_file.write("N/A")
				log_file.write(",\"angle\":")
				log_file.write("N/A")
				log_file.write(",\"brush\":")
				log_file.write("N/A")
				log_file.write("}")				
		if quit==1:
			break

def watchDog(control_id):
	global dog
	global watch_time
	global quit
	global port
	global serial_write_control
	
	while True:
		time.sleep(watch_time)
		if(dog==0):
			while serial_write_control!=0:
				pass
			serial_write_control = control_id
			port.write('0')
			serial_write_control = 0
		dog = 0
		if qui==1:
			break



signal.signal(signal.SIGINT, signal_handler)
thread.start_new_thread(Send_Data, (1,))
thread.start_new_thread(Receive_Data, (2,))
thread.start_new_thread(watchDog, (3,))

while True:
	if quit==1:
		port.close()
		ss.close()
		sys.exit(0)
