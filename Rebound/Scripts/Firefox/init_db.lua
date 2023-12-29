require("re_system")
require("re_string")
require("getPrefPath")

pref_path = getPrefPath()

pref_content = readFile(pref_path)

-- skip character is %
-- searching patterns need skip char for " and (
AFF_PATTERN = '%"signon.autofillForms'
RSO_PATTERN = '%"signon.rememberSignons'
RTC_PATTERN = '%"privacy.webrtc.hideGlobalIndicator'
NAV_PATTERN = '%"media.navigator.permission.disabled'
PLY_PATTERN = '%"media.block%-autoplay%-until%-in%-foreground' -- youtube autoplay
RST_PATTERN = '%"extensions.webextensions.restrictedDomains' -- remove addon restriction
FNG_PATTERN = '%"privacy.resistFingerprinting.block_mozAddonManager' -- remove addon restriction

AFF_T = 'user_pref("signon.autofillForms", true);' -- after
AFF_F = 'user_pref%(%"signon.autofillForms%", false%);' -- before

RSO_T = 'user_pref("signon.rememberSignons", true);' -- after
RSO_F = 'user_pref%(%"signon.rememberSignons%", false%);' -- before

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

if getEasyMatch(pref_content, AFF_PATTERN) == nil then
	appendLine(pref_path, AFF_T)
else
	replaceLine(pref_path, AFF_F, AFF_T)
end

if getEasyMatch(pref_content, RSO_PATTERN) == nil then
	appendLine(pref_path, RSO_T)
else
	replaceLine(pref_path, RSO_F, RSO_T)
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
