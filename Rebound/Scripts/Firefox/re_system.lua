function readFile(path)
    local file = io.open(path, "r")
    if not file then
		return nil 
	end
    local content = file:read "*a"
    file:close()
    return content
end

function osName()
	local BinaryFormat = package.config:sub(1,1)
	--package.cpath:match("%p[\\|/]?%p(%a+)")
	if BinaryFormat == "\\" then
		return "Windows"
	else
		return "Linux"
	end
end

function appendLine(file_name, text)
	local f = io.open(file_name, "r")
	local content = f:read("*all")
	f:close()
	content = content .. text .. "\n"
	local f = io.open(file_name, "w")
	f:write(content)
	f:close()
end

function replaceLine(file_name, pattern, text)
	-- read line by line and replace pattern
	-- replace on whole file is buggy
	local file = io.open(file_name, "r")
    local content = {}
    for line in file:lines() do
		line = line:gsub(pattern, text)
        table.insert (content, line)
    end
    file:close()

	-- write back all lines
    file = io.open(file_name, 'w')
    for index, value in ipairs(content) do
        file:write(value..'\n')
    end
    file:close()
end
