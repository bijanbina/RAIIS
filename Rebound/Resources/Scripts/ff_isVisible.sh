#!/bin/bash
# firefox need to execute "Runtime.enable" first on target
# then with an added delay execute "Runtime.evaluate"!

#Tag Screen 1
TAG1=$(awesome-client "return screen[2].selected_tag.name")
TAG1=$(echo "$TAG1" | cut -d\" -f2)
TAG1=$(( TAG1 + 5 ))

#Tag Screen 2
TAG2=$(awesome-client "return screen[1].selected_tag.name")
TAG2=$(echo "$TAG2" | cut -d\" -f2)
TAG2=$(( TAG2 - 1 ))

WIN_LIST=$(wmctrl -l | grep "— Mozilla Firefox" | grep "$1")
WIN_TAG=$(echo $WIN_LIST | cut -d' ' -f2)
if [[ "$WIN_TAG" == "$TAG1" ]]; then
	echo y
elif [[ "$WIN_TAG" == "$TAG2" ]]; then
	echo y
fi