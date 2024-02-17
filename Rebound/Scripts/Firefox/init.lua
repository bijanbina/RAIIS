-- This file is executed when rebound starts

require("re_system")
require("re_string")
require("getPrefPath")

pref_path = getPrefPath()

pref_content = readFile(pref_path)

CRM_PATTERN = 'devtools.chrome.enabled'
REM_PATTERN = 'devtools.debugger.remote%-enabled'
WBS_PATTERN = 'devtools.debugger.remote%-websocket'
THM_PATTERN = 'toolkit.legacyUserProfileCustomizations.stylesheets'
UBI_PATTERN = 'app.update.background.interval'
UPD_PATTERN = 'app.update.interval'
URL_PATTERN = 'browser.safebrowsing.provider.google.updateURL'

RTC_PATTERN = '%"privacy.webrtc.hideGlobalIndicator'
NAV_PATTERN = '%"media.navigator.permission.disabled'
PLY_PATTERN = '%"media.block%-autoplay%-until%-in%-foreground' -- youtube autoplay
RST_PATTERN = '%"extensions.webextensions.restrictedDomains' -- remove addon restriction
FNG_PATTERN = '%"privacy.resistFingerprinting.block_mozAddonManager' -- remove addon restriction
SGN_PATTERN = '%"xpinstall.signatures.required' -- remove addon restriction

CRM_LINE = 'user_pref("devtools.chrome.enabled", true);'
REM_LINE = 'user_pref("devtools.debugger.remote-enabled", true);'
WBS_LINE = 'user_pref("devtools.debugger.remote-websocket", true);'
THM_LINE = 'user_pref("toolkit.legacyUserProfileCustomizations.stylesheets", true);'
UBI_LINE = 'user_pref("app.update.background.interval", -1);'
UPD_LINE = 'user_pref("app.update.interval", -1);'
URL_LINE = 'user_pref("browser.safebrowsing.provider.google.updateURL", "lolo");'

RTC_T = 'user_pref("privacy.webrtc.hideGlobalIndicator", true);' -- after
RTC_F = 'user_pref%(%"privacy.webrtc.hideGlobalIndicator%", false%);' -- before

NAV_T = 'user_pref("media.navigator.permission.disabled", true);' -- after
NAV_F = 'user_pref%(%"media.navigator.permission.disabled%", false%);' -- before

PLY_T = 'user_pref%(%"media.block%-autoplay%-until%-in%-foreground%", true%);' -- before
PLY_F = 'user_pref("media.block-autoplay-until-in-foreground", false);' -- after

RST_A = 'user_pref("extensions.webextensions.restrictedDomains", "");' -- after
RST_B = 'user_pref%(%"extensions.webextensions.restrictedDomains%", %".*%"%);' -- before

FNG_T = 'user_pref%(%"privacy.resistFingerprinting.block_mozAddonManager%", true%);' -- before
FNG_F = 'user_pref("privacy.resistFingerprinting.block_mozAddonManager", false);' -- after

SGN_T = 'user_pref%(%"xpinstall.signatures.required%", true%);' -- before
SGN_F = 'user_pref("xpinstall.signatures.required", false);' -- after

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

if getFirstMatch(pref_content, UBI_PATTERN) == nil then
	appendLine(pref_path, UBI_LINE)
end

if getFirstMatch(pref_content, UPD_PATTERN) == nil then
	appendLine(pref_path, UPD_LINE)
end

if getEasyMatch(pref_content, RTC_PATTERN) == nil then
	appendLine(pref_path, RTC_T)
else
	replaceLine(pref_path, RTC_F, RTC_T)
end

if getEasyMatch(pref_content, NAV_PATTERN) == nil then
	appendLine(pref_path, NAV_T)
else
	replaceLine(pref_path, NAV_F, NAV_T)
end

if getEasyMatch(pref_content, PLY_PATTERN) == nil then
	appendLine(pref_path, PLY_F)
else
	replaceLine(pref_path, PLY_T, PLY_F)
end

if getEasyMatch(pref_content, RST_PATTERN) == nil then
	appendLine(pref_path, RST_A)
else
	replaceLine(pref_path, RST_B, RST_A)
end

if getEasyMatch(pref_content, FNG_PATTERN) == nil then
	appendLine(pref_path, FNG_F)
else
	replaceLine(pref_path, FNG_T, FNG_F)
end

if getEasyMatch(pref_content, SGN_PATTERN) == nil then
	appendLine(pref_path, SGN_F)
else
	replaceLine(pref_path, SGN_T, SGN_F)
end

print(osName())
if osName() == "Windows" then
	chrome_path = getChromePath()
	os.execute("mkdir " .. chrome_path)
	os.execute("copy userChrome.css " .. chrome_path)
end