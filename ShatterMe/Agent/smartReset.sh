#!/bin/bash
echo "4" > /sys/class/gpio/export 
echo "5" > /sys/class/gpio/export
echo "out" > /sys/class/gpio/gpio4/direction
echo "in" > /sys/class/gpio/gpio5/direction
snmpd -Lo &
snmp_pid="$!"
/root/Projects/RAIIS/ShatterMe/ShatterMe &
shit_pid="$!"
echo "snmp pid: $snmp_pid"
echo "shit pid: $shit_pid"
while true; do
    if [ `cat /sys/class/gpio/gpio5/value` -eq 0 ];then
		kill $snmp_pid
		kill $shit_pid
		wait $snmp_pid
		wait $shit_pid
		snmpd -Lo &
		snmp_pid="$!"
		/root/Projects/RAIIS/ShatterMe/ShatterMe &
		shit_pid="$!"
		echo "Code:1"
		echo "Code:2"
		sleep 10
		echo "Code:3"
		if [ `cat /sys/class/gpio/gpio5/value` -eq 0 ];then
				echo "We are going to die"
				reboot
		fi
	fi
	sleep 0.1
done

