# How To Start

Install nodemcu-uploader by running

```
sudo pip2 install nodemcu-uploader
```

# Use timer
Somewhere inside codes, timer used instead of direct function call.
The reason is ESP8266 runs some assessment codes, each 1000 clock.  Thus executing long functions interrupt the process and will  cause the following error to appear

```
rst cause:2, boot mode:(3,6)
```

To prevent that, simply use a time and a callback to break a long function into smaller pieces

# gedit Scripts
following scripts helping to automate the uploading process in gedit.

### F5

```
#!/bin/sh
nPid=$(pgrep gtkterm)
if [[ ! -z "$nPid" ]];then
	kill $nPid 
	while [[ $(ps -p 10497 | grep gtkterm) ]]; do
		sleep 0.5
	done
fi
##This line compile and remove lua file
nodemcu-uploader upload "$GEDIT_CURRENT_DOCUMENT_NAME" --compile
##nodemcu-uploader file remove '$GEDIT_CURRENT_DOCUMENT_NAME'
nodemcu-uploader file list
nodemcu-uploader node restart
sleep 2
gtkterm &
```

### Ctrl+R

```
#!/bin/sh
nPid=$(pgrep gtkterm)
if [[ ! -z "$nPid" ]];then
	kill $nPid 
	while [[ $(ps -p 10497 | grep gtkterm) ]]; do
		sleep 0.5
	done
fi
nodemcu-uploader file remove init.lua
```

### F4

```
#!/bin/sh
nPid=$(pgrep gtkterm)
if [[ ! -z "$nPid" ]];then
	kill $nPid 
	while [[ $(ps -p 10497 | grep gtkterm) ]]; do
		sleep 0.5
	done
fi
nodemcu-uploader upload init.lua
sleep 1
nodemcu-uploader node restart
sleep 1
gtkterm &
```
