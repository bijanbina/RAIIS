require("re_system")
require("re_string")

function getProfPathWin()
	local ff_path = os.getenv("APPDATA")
	ff_path = ff_path .. "\\Mozilla\\Firefox"
	local prof_path = ff_path .. "\\profiles.ini"
	
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

function getProfPathLinux()
	local ff_path = os.getenv("HOME")
	ff_path = ff_path .. "/.mozilla/firefox/"
	local prof_path = ff_path .. "profiles.ini"
	
	fileContent = readFile(prof_path);
	prof_name = getFirstDefault(fileContent, "Default")
	
	local pn_split = {}
	for str in prof_name:gmatch("([^".."=".."]+)") do  
		pn_split[#pn_split + 1] = str
	end

	prof_name = pn_split[2]
	return ff_path .. prof_name
end

function getChromePath()
	local os_type = getOsType()
	if os_type=="win" then
		prof_path = getProfPathWin()
		chrome_path = prof_path .. "\\chrome"
	else
		prof_path = getProfPathLinux()
		chrome_path = prof_path .. "/chrome"
	end
	return chrome_path
end

function getPrefPath()
	local os_type = getOsType()
	if os_type=="win" then
		prof_path = getProfPathWin()
		pref_path = prof_path .. "\\prefs.js"
	else
		prof_path = getProfPathLinux()
		pref_path = prof_path .. "/prefs.js"
	end
	return pref_path
end
