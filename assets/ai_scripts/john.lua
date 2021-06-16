------------ JOHN AI

--[[
Info available to the ai
mapinfo.player { x, y, z }
mapinfo.raw { {x, y, z, type }, ...}
mapinfo.dist { }
]]
------------

------ Debug variables
local debug = true

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
Danger = {}

-----  Map functions
function PrintMap(map, MaxX, maxZ)
	log("---------")
	log("PRINT MAP")
	log("---------")
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
	--PrintMap(map, MaxX, MaxY)
	return map
end

function CreateDangerMap(dangers)
	local danger = {}
    for i=0,MaxX + 1 do
    	danger[i] = {}
    	for j=0,MaxY + 1 do
    		danger[i][j] = 0
    	end
    end
	for i, zone in ipairs(dangers) do
		danger[math.floor(zone.x)][math.floor(zone.y)] = math.floor(zone.level)
	end
	--PrintMap(danger, MaxX, MaxY)
	return danger
end

function isInExplosionRange(mapinfo, x, y)
	for i, danger in ipairs(mapinfo.danger) do
		if Danger[x][y] > 0 then
			return true
		end
	end
	return false
end

---- Pathfinding

function setAdd(set, toAdd)
	table.insert(set, toAdd)
end

function setRemove(set, toRemove)
	for i, node in ipairs(set) do
		if node == toRemove then
			set[i] = set[#set]
			set[#set] = nil
			break
		end
	end
end

function not_in(set, node)
	for _,value in pairs(set) do
		if value == node then
			return false
		end
	end
	return true
end


function getNeighbors(node)
	local neighbors = {}
	for dir in Dirs do
		local neighborX = node.x + dir.x
		local neighborY = node.y + dir.y

		if neighborY <= MaxY and neighborX <= MaxX then
			if neighborY >= 0 and neighborX >= 0 then
				if Map[neighborX][neighborY] == 0 then
					table.insert(neighbors, {x = neighborX, y = neighborY})
				end
			end
		end
	end
end

function getLowestFromSet(set, f_score)
	local lowest = 100000
	local best = nil
	for _,node in ipairs(set) do
		local score = f_score[node]
		if score < lowest then
			lowest = score
			best = node
		end
	end
	return best
end

function fill_path(path, came_from, node)
	if came_from[node] then
		table.insert(path, 1, came_from[node])
		return fill_path(path, came_from, came_from[node])
	else
		return path
	end
end

--A star search
function pathfind(root, target)
	local closed = {}
	local open = { root }
	local came_from = {}

	local g_score = {}
	local f_score = {}

	g_score[root] = 0
	f_score[root] = dist(root, target)

	while #open > 0 do
		local curr = getLowestFromSet(open, f_score) --get lowest node of openset
		if curr.x == target.x and curr.y == target.y then
			local path = fill_path({}, came_from, target) -- fill the path with came from
			table.insert(path, target)
			return path
		end
		setRemove(open, curr) -- remove curr from open
		setAdd(closed, curr)-- add node to closed

		local neighbors = getNeighbors(curr) -- get neighbors of current
		for _, neighbor in ipairs(neighbors) do
			if not_in(closed, neighbor) then -- neighbor not in closed set
				local try_g_score = g_score[curr] + 1
				if not_in(open, neighbor) or try_g_score < g_score[neighbor] then
					came_from[neighbor] = curr
					g_score[neighbor] = try_g_score
					f_score[neighbor] = g_score[neighbor] + dist(neighbor, target)
					if not_in(open, neighbor) then
						setAdd(open, neighbor)
					end
				end
			end
		end
	end
end

function dist(nodeA, nodeB)
	return math.sqrt(math.pow(nodeB.x - nodeA.x, 2) + math.pow(nodeB.y - nodeA.y, 2))
end

function getPathToSafeSpace(player)
	local minXesc = (player.x - 3 < 0) and 0 or (player.x - 3);
	local MaxXesc = (player.x + 3 > MaxX) and MaxX or (player.x + 3);
	local minYesc = (player.y - 3 < 0) and 0 or (player.y - 3);
	local MaxYesc = (player.y + 3 > MaxY) and MaxY or (player.y + 3);

	local maybeSafeSpace = {}
	for i=minXesc,MaxXesc do
		for j=minYesc, MaxYesc do
			if Map[i][j] == 0 and Danger[i][j] == 0 then
				table.insert(maybeSafeSpace, {x = i, y = j})
			end
		end
	end
	local minDist = 100000
	local res = {}
	for _, safe in ipairs(maybeSafeSpace) do
		local currDist = dist(player, safe)
		if currDist < minDist then
			minDist, res = currDist, safe
		end
	end
	local path = pathfind(player, res)
	for _, n in ipairs(path) do
		print("x")
		print(n.x)
		print("y")
		print(n.y)
	end
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
	Danger = CreateDangerMap(mapinfo.danger)
	--PrintMap(Danger, MaxX, MaxY)
	local roundedPlayerPos = {x = math.floor(mapinfo.player.x+0.5), y = math.floor(mapinfo.player.y+0.5)}
	if (isInExplosionRange(mapinfo, roundedPlayerPos.x, roundedPlayerPos.y)) then
		local pathToSafeSpace = getPathToSafeSpace(roundedPlayerPos)
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