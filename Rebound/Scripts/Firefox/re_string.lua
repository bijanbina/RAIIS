function getFirstMatch(text, pattern)
	for line in string.gmatch(text, "[^\r\n]+") do
		if line:match('%f[%a]'..pattern..'%f[%A]') ~= nil then
            return line
		end
    end
end

function getFirstDefault(text, pattern)
	for line in string.gmatch(text, "[^\r\n]+") do
		if line:match('%f[%a]'..pattern..'%f[%A]') ~= nil and line:match(pattern..'%=1') == nil then
            return line
		end
    end
end

function getEasyMatch(text, pattern)
	for line in string.gmatch(text, "[^\r\n]+") do
		if line:match(pattern) ~= nil then
            return line
		end
    end
end
