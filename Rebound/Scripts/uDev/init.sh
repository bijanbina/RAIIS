#!/bin/bash

WD=$(dirname "$0")
cp $WD/10-uinput.rules /etc/udev/rules.d/
chmod 777 /dev/uinput

#udevadm control --reload
#udevadm trigger