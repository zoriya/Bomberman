------------ JOHN AI

--[[
Info available to the ai
mapinfo.player { x, y, z }
mapinfo.raw { {x, y, z, type }, ...}
mapinfo.dist { }
]]
------------


local debug = false

if not debug then
    log = function() end
else
	log = function(a)
		print(a)
	end
end

function PrintMap(map, maxX, maxZ)
	for i=0,maxX + 1 do
		local s = "| "
    	for j=0,maxZ + 1 do
			s = s .. tostring(map[i][j]) .. " | ";
		end
		log(s)
		log(string.rep("-", (maxZ - 1) * 5 - 1))
    end
end

function CreateMyMap(infos, maxX, maxY)
	local map = {}
    for i=0,maxX + 1 do
    	map[i] = {}
    	for j=0,maxY + 1 do
    		map[i][j] = 0
    	end
    end
	for i, info in ipairs(infos) do
		map[info.x][info.y] = info.type
	end
	PrintMap(map, maxX, maxY)
	return map
end

function isInExplosionRange(mapinfo, x, y)
	for i, danger in ipairs(mapinfo.danger) do
		if danger.x == x and danger.y == y then
			return true
		end
	end
	return false
end

function Update(mapinfo)
	local maxX = 0
	local maxY = 0
	for i, info in ipairs(mapinfo.raw) do
		if info.x > maxX then
			maxX = info.x
		end
		if info.y > maxY then
			maxY = info.y
		end
	end
	local roundedPlayerPos = {x = math.floor(mapinfo.player.x+0.5), y = math.floor(mapinfo.player.y+0.5)}
	local myMap = CreateMyMap(mapinfo.raw, maxX, maxY)
	if (isInExplosionRange(mapinfo, roundedPlayerPos.x, roundedPlayerPos.y)) then
		if (myMap[roundedPlayerPos.x + 1][roundedPlayerPos.y] ~= 0) then
			return -1, 0, false, false
		else
			return 1, 0, false, false
		end
		--play defensive RUN
	else
		return 1, 0, true, true;
		--play offensive
	end
end