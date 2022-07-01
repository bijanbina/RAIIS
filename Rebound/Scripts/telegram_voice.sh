#!/bin/bash

WIN_ID=$(xdotool getactivewindow)
GEOMETRY=$(xdotool getwindowgeometry $WIN_ID)

POSITION=$(echo $GEOMETRY | awk '{print $4'})
POS_X=$(echo $POSITION | cut -d',' -f1)
POS_Y=$(echo $POSITION | cut -d',' -f2)

SIZE=$(echo $GEOMETRY | awk '{print $8'})
WIDTH=$(echo $SIZE | cut -d'x' -f1)
HEIGHT=$(echo $SIZE | cut -d'x' -f2)

echo $POS_X $POS_Y
echo $WIDTH $HEIGHT

MOUSE_X=$(( POS_X + WIDTH - 20 ))
MOUSE_Y=$(( POS_Y + HEIGHT - 20 ))
echo $MOUSE_X $MOUSE_Y

#send go sleep to BaTool
DBUS_PATH="--dest=com.binaee.rebound / com.binaee.rebound"
dbus-send --session $DBUS_PATH.meta string:"6"
dbus-send --session $DBUS_PATH.apps  string:"7"

xdotool mousemove $MOUSE_X $MOUSE_Y
sleep 0.1
xdotool mousedown 1
sleep 0.3
xdotool mousemove_relative 0 -200
sleep 0.5
xdotool mouseup 1