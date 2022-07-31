function getFirstMatch(text, pattern)
	for line in string.gmatch(text, "[^\r\n]+") do
		if line:match('%f[%a]'..pattern..'%f[%A]') ~= nil then
            return line
		end
    end
end