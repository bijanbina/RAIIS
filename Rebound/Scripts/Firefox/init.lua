-- This file is executed when rebound starts

require("re_system")
require("re_string")
require("getPrefPath")

pref_path = getPrefPath()
pref_content = readFile(pref_path)

enableAutoFill()
addPrefLine('signon.autofillForms.http', "true")
addPrefLine('devtools.chrome.enabled', "true")
addPrefLine('toolkit.legacyUserProfileCustomizations.stylesheets', "true")
addPrefLine('app.update.background.interval', "-1")
addPrefLine('app.update.interval', "-1")
addPrefLine('browser.safebrowsing.provider.google.updateURL', '"lolo"')

RTC_PATTERN = '%"privacy.webrtc.hideGlobalIndicator'
RTC_T = 'user_pref("privacy.webrtc.hideGlobalIndicator", true);' -- after
RTC_F = 'user_pref%(%"privacy.webrtc.hideGlobalIndicator%", false%);' -- before
if getEasyMatch(pref_content, RTC_PATTERN) == nil then
	appendLine(pref_path, RTC_T)
else
	replaceLine(pref_path, RTC_F, RTC_T)
end

NAV_PATTERN = '%"media.navigator.permission.disabled'
NAV_T = 'user_pref("media.navigator.permission.disabled", true);' -- after
NAV_F = 'user_pref%(%"media.navigator.permission.disabled%", false%);' -- before
if getEasyMatch(pref_content, NAV_PATTERN) == nil then
	appendLine(pref_path, NAV_T)
else
	replaceLine(pref_path, NAV_F, NAV_T)
end

PLY_PATTERN = '%"media.block%-autoplay%-until%-in%-foreground' -- youtube autoplay
PLY_T = 'user_pref%(%"media.block%-autoplay%-until%-in%-foreground%", true%);' -- before
PLY_F = 'user_pref("media.block-autoplay-until-in-foreground", false);' -- after
if getEasyMatch(pref_content, PLY_PATTERN) == nil then
	appendLine(pref_path, PLY_F)
else
	replaceLine(pref_path, PLY_T, PLY_F)
end

RST_PATTERN = '%"extensions.webextensions.restrictedDomains' -- remove addon restriction
RST_A = 'user_pref("extensions.webextensions.restrictedDomains", "");' -- after
RST_B = 'user_pref%(%"extensions.webextensions.restrictedDomains%", %".*%"%);' -- before
if getEasyMatch(pref_content, RST_PATTERN) == nil then
	appendLine(pref_path, RST_A)
else
	replaceLine(pref_path, RST_B, RST_A)
end
FNG_PATTERN = '%"privacy.resistFingerprinting.block_mozAddonManager' -- remove addon restriction
FNG_T = 'user_pref%(%"privacy.resistFingerprinting.block_mozAddonManager%", true%);' -- before
FNG_F = 'user_pref("privacy.resistFingerprinting.block_mozAddonManager", false);' -- after
if getEasyMatch(pref_content, FNG_PATTERN) == nil then
	appendLine(pref_path, FNG_F)
else
	replaceLine(pref_path, FNG_T, FNG_F)
end

SGN_PATTERN = '%"xpinstall.signatures.required' -- remove addon restriction
SGN_T = 'user_pref%(%"xpinstall.signatures.required%", true%);' -- before
SGN_F = 'user_pref("xpinstall.signatures.required", false);' -- after
if getEasyMatch(pref_content, SGN_PATTERN) == nil then
	appendLine(pref_path, SGN_F)
else
	replaceLine(pref_path, SGN_T, SGN_F)
end

TRN_PATTERN = '%"browser.translations.automaticallyPopup' -- remove translator popup
TRN_T = 'user_pref%(%"browser.translations.automaticallyPopup%", true%);' -- before
TRN_F = 'user_pref("browser.translations.automaticallyPopup", false);' -- after
if getEasyMatch(pref_content, TRN_PATTERN) == nil then
	appendLine(pref_path, TRN_F)
else
	replaceLine(pref_path, TRN_T, TRN_F)
end

-- print(osName())
chrome_path = getChromePath()
if osName() == "Windows" then
	os.execute("mkdir " .. chrome_path)
	os.execute("copy userChrome.css " .. chrome_path)
else -- Linux
	os.execute("mkdir -p " .. chrome_path)
	os.execute("cp userChrome.css " .. chrome_path)
end
