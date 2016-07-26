#!/bin/bash
echo "4" > /sys/class/gpio/export 
echo "5" > /sys/class/gpio/export
echo "out" > /sys/class/gpio/gpio4/direction
echo "in" > /sys/class/gpio/gpio5/direction
while true; do
    if [ `cat /sys/class/gpio/gpio5/value` -eq 0 ];then
		pkill ShatterMe
		pkill snmp
		snmpd -Lo
		echo "Code:1"
		/root/Projects/RAIIS/ShatterMe/ShatterMe &
		disown
		echo "Code:2"
		sleep 10
		echo "Code:3"
		if [ `cat /sys/class/gpio/gpio5/value` -eq 0 ];then
				echo "We are going to dye"
				reboot
		fi
	fi
	sleep 0.1
done
