#!/bin/bash
echo "4" > /sys/class/gpio/export 
echo "5" > /sys/class/gpio/export
echo "out" > /sys/class/gpio/gpio4/direction
echo "in" > /sys/class/gpio/gpio5/direction
while true; do
    #echo "1" > /sys/class/gpio/gpio4/value
    sleep 0.05
    #echo "0" > /sys/class/gpio/gpio4/value
    sleep 0.05
done
