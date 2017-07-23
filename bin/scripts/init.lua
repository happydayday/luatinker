
--
	local _path = package.path
	package.path = string.format(
	"%s;%s/?.lua;%s/?/init.lua", _path, ROOT, ROOT )

-- reload()
function reload(name)
	local old_module = require(name)
	package.loaded[name] = nil
	local new_module = require(name)
	if type( new_module ) == "table" then
		for k,v in pairs(new_module) do
			old_module[k] = v
		end
	end
	package.loaded[name] = old_module
end

local key = ""
function print_table(arg, level)
	level = level or 1
	local indent = ""
	for i = 1, level do
		indent = indent.."  "
	end

	if key ~= "" then
    	print(indent..key.." ".."=".." ".."{")
	else
		print(indent .. "{")
	end

	key = ""
	for k, v in pairs(arg) do
		if type( v ) ~= "table" then
			local content = string.format("%s%s = %s", indent .. "  ",tostring(k), tostring(v))
			print(content)
		else
			key = k
			print_table( v, level + 1 )
		end
	end
	print( indent .. "}")
end
