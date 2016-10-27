# How To Start

Install nodemcu-uploader by running

```
sudo pip2 install nodemcu-uploader
```

# Use timer
Somewhere inside codes, timer used instead of direct function call.
The reason is ESP8266 need to run some commands every 1000 clock so if the function is a callback and it's too long it needs to breck into other function and called by a timer otherwise following error appear
```
rst cause:2, boot mode:(3,6)
```


# gEdit Scripts
use following script in gEdit to automate proccess

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
