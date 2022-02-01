#!/bin/bash

DBUS_DEST="org.mpris.MediaPlayer2.spotify"
DBUS_NAME="/org/mpris/MediaPlayer2 org.freedesktop.DBus.Properties.Get"
DBUS_ARGS="string:org.mpris.MediaPlayer2.Player string:PlaybackStatus"

STATUS=$(dbus-send --print-reply --dest=$DBUS_DEST $DBUS_NAME $DBUS_ARGS 2>/dev/null)

if [[ "$?" == "1" ]]; then

	DBUS_DEST=$(qdbus --session | grep org.mpris)
	DBUS_DEST="${DBUS_DEST:1}"
	
fi

if [[ "$1" == "play" ]]; then

	DBUS_NAME="/org/mpris/MediaPlayer2"
	DBUS_FUNC="org.mpris.MediaPlayer2.Player.PlayPause"
	dbus-send --print-reply --dest=$DBUS_DEST $DBUS_NAME $DBUS_FUNC

elif [[ "$1" == "next" ]]; then

	DBUS_NAME="/org/mpris/MediaPlayer2"
	DBUS_FUNC="org.mpris.MediaPlayer2.Player.Next"
	dbus-send --print-reply --dest=$DBUS_DEST $DBUS_NAME $DBUS_FUNC

elif [[ "$1" == "prev" ]]; then

	DBUS_NAME="/org/mpris/MediaPlayer2"
	DBUS_FUNC="org.mpris.MediaPlayer2.Player.Previous"
	dbus-send --print-reply --dest=$DBUS_DEST $DBUS_NAME $DBUS_FUNC

fi
