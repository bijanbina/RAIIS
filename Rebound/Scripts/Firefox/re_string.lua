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

function addPrefLine(pattern, value)
	local line = string.format('user_pref("%s", %s);', pattern, tostring(value))
	print(line)
	if getFirstMatch(pref_content, pattern) == nil then
		appendLine(pref_path, line)
	end
end

--[[  add_country_from_region
      • Works on global pref_content
      • Adds/creates the supportedCountries pref so it always contains the region.
--]]
function enableAutoFill()
    --------------------------------------------------------------------
    -- 1. Grab the region from browser.search.region
    --------------------------------------------------------------------
    local region = pref_content:match(
        'user_pref%("browser%.search%.region"%s*,%s*"([^"]+)"%);')

    print("[DEBUG] Region detected: " .. tostring(region))

    if not region then
        print("[WARN ] Region line not found - nothing to do.")
        return false
    end

    --------------------------------------------------------------------
    -- 2. Try to patch existing supportedCountries line
    --------------------------------------------------------------------
    local modified = false
    pref_content, n = pref_content:gsub(
        'user_pref%("extensions%.formautofill%.addresses%.supportedCountries"%s*,%s*"([^"]*)"%)%;',
        function(list)
            print("[DEBUG] Found supportedCountries: " .. list)

            if ("," .. list .. ","):find("," .. region .. ",") then
                print("[INFO ] " .. region .. " already present - no change.")
                return ('user_pref("extensions.formautofill.addresses.supportedCountries", "%s");')
                       :format(list)   -- unchanged
            end

            local updated = list .. "," .. region
            print("[INFO ] Updated supportedCountries: " .. updated)
            modified = true
            return ('user_pref("extensions.formautofill.addresses.supportedCountries", "%s");')
                   :format(updated)
        end,
        1)  -- only first match

    --------------------------------------------------------------------
    -- 3. If the line was missing entirely, add a new one.
    --------------------------------------------------------------------
    if n == 0 then
        print("[WARN ] supportedCountries line not found - creating a new one.")
        local default_list = "US,CA,FR,DE"
        if not ("," .. default_list .. ","):find("," .. region .. ",") then
            default_list = default_list .. "," .. region
        end
        local new_line = ('user_pref("extensions.formautofill.addresses.supportedCountries", "%s");')
                        :format(default_list)

        appendLine(pref_path, new_line)
        modified = true
		--"extensions.formautofill.addresses.supported", "on")
		--"extensions.formautofill.available", "on")
    end
end
