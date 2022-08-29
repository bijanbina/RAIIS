require("re_system")
require("re_string")

function getProfPath()
	local ff_path = os.getenv("APPDATA")
	local ff_path = ff_path .. "\\Mozilla\\Firefox"
	prof_path = ff_path .. "\\profiles.ini"
	
	fileContent = readFile(prof_path);
	prof_name = getFirstDefault(fileContent, "Default")
	
	local pn_split = {}
	for str in prof_name:gmatch("([^".."=".."]+)") do  
		pn_split[#pn_split + 1] = str
	end

	prof_name = pn_split[2]
	prof_name = prof_name:gsub( "/", "\\")
	
	return ff_path .. "\\" .. prof_name
end

function getChromePath()
	prof_path = getProfPath()
	chrome_path = prof_path .. "\\chrome"
	return chrome_path
end

function getPrefPath()
	prof_path = getProfPath()
	pref_path = prof_path .. "\\prefs.js"
	return pref_path
end