require("re_system")
require("re_string")

url_list = ""

function printUrl(text)
	local url_split = {}
	for str in text:gmatch("([^".."\"".."]+)") do  
		url_split[#url_split + 1] = str
	end
	
	url_list = url_list .. url_split[4] .. "\n"
end

function printAddress(text, pattern)
	local i = 0
	local print_i = 0
	for line in text:gmatch("[^\r\n]+") do
		i = i + 1
		if line:find(pattern) then
			print_i = i + 2
		end
		if i == print_i then
			printUrl(line)
			print_i = 0
		end
    end
end

os.execute(".\\win32_dl.vbs")

list_content = readFile("list.json")

list_content = list_content:gsub( "localhost", "127.0.0.1")
printAddress(list_content, '"type": "page",')