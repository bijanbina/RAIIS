function getOsType()
	local os_separator = package.config:sub(1,1)
	if os_separator=="\\" then
		return "win"
	else
		return "linux"
	end
end

function getFirstMatch(text, pattern)
	if os_type=="win" then
		newline_char = "\r\n"
	else
		newline_char = "\n"
	end
	
	for line in string.gmatch(text, "[^" .. newline_char .. "]+") do
		if line:match('%f[%a]'..pattern..'%f[%A]') ~= nil then
            return line
		end
    end
end

function getFirstDefault(text, pattern)
	if os_type=="win" then
		newline_char = "\r\n"
	else
		newline_char = "\n"
	end
	
	for line in string.gmatch(text, "[^" .. newline_char .. "]+") do
		if line:match('%f[%a]'..pattern..'%f[%A]') ~= nil and line:match(pattern..'%=1') == nil then
            return line
		end
    end
end

function getEasyMatch(text, pattern)
	for line in string.gmatch(text, "[^" .. newline_char .. "]+") do
		if line:match(pattern) ~= nil then
            return line
		end
    end
end
