require("re_system")
require("re_string")
require("getPrefPath")

pref_path = getPrefPath()

pref_content = readFile(pref_path)

CRM_PATTERN = 'devtools.chrome.enabled'
REM_PATTERN = 'devtools.debugger.remote-enabled'
WBS_PATTERN = 'devtools.debugger.remote-websocket'
THM_PATTERN = 'toolkit.legacyUserProfileCustomizations.stylesheets'

CRM_LINE = 'user_pref("devtools.chrome.enabled", true);'
REM_LINE = 'user_pref("devtools.debugger.remote-enabled", true);'
WBS_LINE = 'user_pref("devtools.debugger.remote-websocket", true);'
THM_LINE = 'user_pref("toolkit.legacyUserProfileCustomizations.stylesheets", true);'

if getFirstMatch(pref_content, CRM_PATTERN) == nil then
	appendLine(pref_path, CRM_LINE)
end

if getFirstMatch(pref_content, REM_PATTERN) == nil then
	appendLine(pref_path, REM_LINE)
end

if getFirstMatch(pref_content, WBS_PATTERN) == nil then
	appendLine(pref_path, WBS_LINE)
end

if getFirstMatch(pref_content, THM_PATTERN) == nil then
	appendLine(pref_path, THM_LINE)
end

print(osName())
if osName() == "Windows" then
	chrome_path = getChromePath()
	os.execute("mkdir " .. chrome_path)
	os.execute("copy userChrome.css " .. chrome_path)
end