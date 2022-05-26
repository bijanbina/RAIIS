#!/bin/bash
# firefox need to execute "Runtime.enable" first on target
# then with an added delay execute "Runtime.evaluate"!

CURL_OUT=$(curl -s http://127.0.0.1:9222/json/list)
WS_URL=$(echo "$CURL_OUT" | grep -A 2 '"type": "page",')
WS_URL=$(echo "$WS_URL" | grep '"webSocketDebuggerUrl"')
WS_URL=$(echo "$WS_URL" | cut -d\" -f4)
cd "$(dirname "$0")"
#websocat known bug: https://github.com/vi/websocat/issues/23
for i in $WS_URL; do
	
	# URL=$(echo "$CURL_OUT" | grep -B 1 $i | head -n1)
	#replace localhost with 127.0.0.1 (known bug)
	i=${i/"localhost"/"127.0.0.1"}
	echo "$i"

done