require("re_system")
require("re_string")
require("getPrefPath")

pref_path = getPrefPath()

pref_content = readFile(pref_path)

AFF_PATTERN = '%"signon.autofillForms'
RSO_PATTERN = '%"signon.rememberSignons'

AFF_T = 'user_pref("signon.autofillForms", true);'
AFF_F = 'user_pref%(%"signon.autofillForms%", false%);'

RSO_T = 'user_pref("signon.rememberSignons", true);'
RSO_F = 'user_pref%(%"signon.rememberSignons%", false%);'

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
