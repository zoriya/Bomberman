------------ JOHN AI

--[[
Info available to the ai
mapinfo.player { x, y, z }
mapinfo.raw { {x, y, z, type }, ...}
mapinfo.dist { }
]]
------------

------ Debug variables
local debug = false

if not debug then
    log = function() end
else
	log = function(a)
		print(a)
	end
end
-----  Global variables
Dirs = {{x = 1, y = 0}, {x = -1, y = 0}, {x = 0, y = -1}, {x = 0, y = 1}}
MaxX = 0
MaxY = 0
Map = {}

-----  Map functions
function PrintMap(map, MaxX, maxZ)
	for i=0,MaxX + 1 do
		local s = "| "
    	for j=0,maxZ + 1 do
			s = s .. tostring(map[i][j]) .. " | ";
		end
		log(s)
		log(string.rep("-", (maxZ - 1) * 5 - 1))
    end
end

function CreateMyMap(infos, MaxX, MaxY)
	local map = {}
    for i=0,MaxX + 1 do
    	map[i] = {}
    	for j=0,MaxY + 1 do
    		map[i][j] = 0
    	end
    end
	for i, info in ipairs(infos) do
		map[info.x][info.y] = info.type
	end
	PrintMap(map, MaxX, MaxY)
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


---- Pathfinding
function pathfind(root, target)
	local closed = {}
	local open = {}
	local came_from = {}
end

function dist(nodeA, nodeB)
	return math.sqrt(math.pow(nodeB.x - nodeA.x, 2) + math.pow(nodeB.y - nodeA.y, 2))
end

function getPathToSafeSpace(player, danger)
	local minXesc = (player.x - 3 < 0) and 0 or (player.x - 3);
	local MaxXesc = (player.x + 3 > MaxX) and MaxX or (player.x + 3);
	local minYesc = (player.y - 3 < 0) and 0 or (player.y - 3);
	local MaxYesc = (player.y + 3 > MaxY) and MaxY or (player.y + 3);

	local maybeSafeSpace = {}
	for i=minXesc,MaxXesc do
		for j=minYesc, MaxYesc do
			if myMap[i][j] == 0 or danger[i][j] == 0 then
				table.insert(maybeSafeSpace, {x = i, y = j})
			end
		end
	end
	local minDist = 100000
	local res = {}
	for safe in pairs(maybeSafeSpace) do
		local currDist = dist(player, safe)
		if currDist < minDist then
			minDist, res = currDist, safe
		end
	end
	local path = pathfind(player, res)
end


------ Update
function Update(mapinfo)
	MaxX = 0
	MaxY = 0
	for i, info in ipairs(mapinfo.raw) do
		if info.x > MaxX then
			MaxX = info.x
		end
		if info.y > MaxY then
			MaxY = info.y
		end
	end
	Map = CreateMyMap(mapinfo.raw, MaxX, MaxY)
	local roundedPlayerPos = {x = math.floor(mapinfo.player.x+0.5), y = math.floor(mapinfo.player.y+0.5)}
	if (isInExplosionRange(mapinfo, roundedPlayerPos.x, roundedPlayerPos.y)) then
		--local pathToSafeSpace = getPathToSafeSpace(roundedPlayerPos)
		if (Map[roundedPlayerPos.x + 1][roundedPlayerPos.y] ~= 0) then
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