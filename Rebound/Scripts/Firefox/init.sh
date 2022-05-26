#!/bin/bash

PROF=$(grep Default ~/.mozilla/firefox/profiles.ini)
PROF=$(echo "$PROF" | head -n 1 | cut -d= -f2)
PROF_PREF=~/.mozilla/firefox/$PROF/prefs.js
#echo "$PROF"

CRM_LINE='user_pref("devtools.chrome.enabled", true);'
REM_LINE='user_pref("devtools.debugger.remote-enabled", true);'
WBS_LINE='user_pref("devtools.debugger.remote-websocket", true);'
THM_LINE='user_pref("toolkit.legacyUserProfileCustomizations.stylesheets", true);'
mkdir -p ~/.mozilla/firefox/$PROF/chrome
cp Scripts/userChrome.css ~/.mozilla/firefox/$PROF/chrome

#chrome.enabled
LN=$(grep -n chrome.enabled $PROF_PREF | cut -d: -f 1)
if [[ "$LN" ]]; then
	sed -i "${LN}s/.*/$CRM_LINE/" $PROF_PREF
else
	echo $CRM_LINE >> $PROF_PREF
fi

#remote-enabled
LN=$(grep -n remote-enabled $PROF_PREF | cut -d: -f 1)
if [[ "$LN" ]]; then
	sed -i "${LN}s/.*/$REM_LINE/" $PROF_PREF
else
	echo $REM_LINE >> $PROF_PREF
fi

#remote-websocket
LN=$(grep -n remote-websocket $PROF_PREF | cut -d: -f 1)
if [[ "$LN" ]]; then
	sed -i "${LN}s/.*/$WBS_LINE/" $PROF_PREF
else
	echo $WBS_LINE >> $PROF_PREF
fi

#legacyUserProfileCustomizations
LN=$(grep -n legacyUserProfileCustomizations $PROF_PREF | cut -d: -f 1)
if [[ "$LN" ]]; then
	sed -i "${LN}s/.*/$THM_LINE/" $PROF_PREF
else
	echo $THM_LINE >> $PROF_PREF
fi