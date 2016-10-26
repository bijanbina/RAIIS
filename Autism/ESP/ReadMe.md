# How To Start

Install nodemcu-uploader by run

```
sudo pip2 install nodemcu-uploader
```

use following script in gEdit to automate proccess

```
#!/bin/sh
##This line compile and remove lua file
nPid=$(pgrep gtkterm)
if [[ ! -z "$nPid" ]];then
	kill $nPid 
	while [[ $(ps -p 10497 | grep gtkterm) ]]; do
		sleep 0.5
	done
fi
nodemcu-uploader upload "$GEDIT_CURRENT_DOCUMENT_NAME" --compile
##nodemcu-uploader file remove '$GEDIT_CURRENT_DOCUMENT_NAME'
nodemcu-uploader file list
nodemcu-uploader node restart
sleep 2
gtkterm &
```
