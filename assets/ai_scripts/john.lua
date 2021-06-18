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
LastPos = nil

-----  Map functions
function PrintMap(map, MaxX, maxZ)
	log("---------")
	log("PRINT MAP")
	log("---------")
	for i=1,MaxX do
		local s = "| "
		for j=1,maxZ do
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
		map[info.x][info.y] = math.floor(info.type)
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
		if danger[math.floor(zone.x)] == nil then
			danger[math.floor(zone.x)] = {}
		end
		danger[math.floor(zone.x)][math.floor(zone.y)] = math.floor(zone.level)
	end
	PrintMap(danger, MaxX, MaxY)
	return danger
end

function isInExplosionRange(x, y)
	if Danger[x][y] > 0 then
			return true
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
		if value.x == node.x and value.y == node.y then
			return false
		end
	end
	return true
end


function getNeighborsDefend(node)
	local neighbors = {}
	for _, dir in ipairs(Dirs) do
		local neighborX = node.x + dir.x
		local neighborY = node.y + dir.y
		if neighborY <= MaxY and neighborX <= MaxX then
			if neighborY >= 0 and neighborX >= 0 then
				if Map[neighborX][neighborY] == 0 and Danger[neighborX][neighborY] ~= 1 then
					table.insert(neighbors, {x = neighborX, y = neighborY})
				end
			end
		end
	end
	if #neighbors == 0 and Danger[node.x][node.y] <= 1 then
		for _, dir in ipairs(Dirs) do
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
	return neighbors
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
	if came_from[node.x][node.y] ~= nil then
		table.insert(path, 1, came_from[node.x][node.y])
		return fill_path(path, came_from, came_from[node.x][node.y])
	else
		return path
	end
end

--A star search
function pathfind(root, target, getNeighborFunc)
	if getNeighborFunc == nil then
		getNeighborFunc = getNeighborsDefend
	end
	local closed = {}
	local open = { root }
	local came_from = {}

	local g_score = {}
	local f_score = {}

	g_score[root] = 0
	f_score[root] = dist(root, target)


	for i=0,MaxX + 1 do
		came_from[i] = {}
		for j=0,MaxY + 1 do
			came_from[i][j] = nil
		end
	end
	while #open > 0 do
		log("openset size")
		log(#open)
		local curr = getLowestFromSet(open, f_score) --get lowest node of openset
		log("current node")
		log(curr.x)
		log(curr.y)
		if curr.x == target.x and curr.y == target.y then
			log("came from")
			local path = fill_path({}, came_from, target) -- fill the path with came from
			table.insert(path, target)
			log("yee")
			return path
		end
		setRemove(open, curr) -- remove curr from open
		setAdd(closed, curr)-- add node to closed
		log("closed set")
		for i, c in ipairs(closed) do
			log("member")
			log(c.x)
			log(c.y)
		end
		local neighbors = getNeighborFunc(curr)
		log("current neightbors") -- get neighbors of current
		log("openset size")
		log(#open)
		for _, neighbor in ipairs(neighbors) do
			log("i")
			if not_in(closed, neighbor) then -- neighbor not in closed set
				log("j")
				local try_g_score = g_score[curr] + 1
				log("g score")
				log(g_score[curr])
				log("g score neig")
				log(g_score[neighbor])
				local g_score_neigh = 10000
				if g_score[neighbor] ~= nil then
					g_score_neigh = g_score[neighbor]
				end
				if not_in(open, neighbor) or try_g_score < g_score_neigh then
					came_from[neighbor.x][neighbor.y] = {x = curr.x, y = curr.y}
					g_score[neighbor] = try_g_score
					f_score[neighbor] = g_score[neighbor] + dist(neighbor, target)
					if not_in(open, neighbor) then
						setAdd(open, neighbor)
					end
				end
			end
		end
	end
	return {}
end

function dist(nodeA, nodeB)
	return math.sqrt(math.pow(nodeB.x - nodeA.x, 2) + math.pow(nodeB.y - nodeA.y, 2))
end

function getPathToSafeSpace(player)
	local minXesc = (player.x - 3 < 0) and 0 or (player.x - 3);
	local MaxXesc = (player.x + 3 > MaxX) and MaxX or (player.x + 3);
	local minYesc = (player.y - 3 < 0) and 0 or (player.y - 3);
	local MaxYesc = (player.y + 3 > MaxY) and MaxY or (player.y + 3);

	local minDist = 100000
	local res = {}
	for i=minXesc,MaxXesc do
		for j=minYesc, MaxYesc do
			if Map[i][j] == 0 and Danger[i][j] == 0 then
				local safe = {x = i, y = j}
				local currDist = dist(player, safe)
				if currDist < minDist then
					minDist, res = currDist, safe
				end
			end
		end
	end
	local path = pathfind(player, res)
	return path
end

function getNeighborAttack(node)
	log("atta")
	local neighbors = {}
	for _, dir in ipairs(Dirs) do
		local neighborX = node.x + dir.x
		local neighborY = node.y + dir.y
		if neighborY <= MaxY and neighborX <= MaxX then
			if neighborY >= 0 and neighborX >= 0 then
				if Map[neighborX][neighborY] <= 1 and Danger[neighborX][neighborY] ~= 1 then
					table.insert(neighbors, {x = neighborX, y = neighborY})
				end
			end
		end
	end
	return neighbors
end

function getPathToEnemy(player, enemies)
	local minDist = 100000
	local res = {}
	for _, enemy in ipairs(enemies) do
		local currDist = dist(player, enemy)
		if currDist < minDist and enemy.x ~= player.x and enemy.y ~= player.y then
			minDist, res = currDist, enemy
		end
	end
	local path = pathfind(player, res, getNeighborAttack)
	return path
end



------ Update
function Update(mapinfo)
	log("NEW FRAME")
	x = getMap()
	PrintMap(x, 16, 16)
	---- sjould send Map Danger and MaxX MaxY
	--MaxX = 0
	--MaxY = 0
	--for i, info in ipairs(mapinfo.raw) do
	--	if info.x > MaxX then
	--		MaxX = info.
	--	end
	--	if info.y > MaxY then
	--		MaxY = info.y
	--	end
	--end
	--Map = CreateMyMap(mapinfo.raw, MaxX, MaxY)
	--Danger = CreateDangerMap(mapinfo.danger)
	--PrintMap(Map, MaxX, MaxY)
	--log("Current player pos")
	--log(mapinfo.player.x)
	--log(mapinfo.player.y)
	--log("Rounded player pos")
	--local roundedPlayerPos = {x = math.floor(mapinfo.player.x+0.5), y = math.floor(mapinfo.player.y+0.5)}
	--log(roundedPlayerPos.x)
	--log(roundedPlayerPos.y)
	--log("Last target")
	--if LastTarget ~= nil then
	--	log(LastTarget.x)
	--	log(LastTarget.y)
	--	if math.abs(LastTarget.x - mapinfo.player.x) <= 0.1 and math.abs(LastTarget.x - mapinfo.player.x) <= 0.1 then
	--		LastTarget = nil
	--	else
	--		return (LastTarget.x - mapinfo.player.x), (LastTarget.y - mapinfo.player.y), false, false
	--	end
	--else
	--	log("No last target")
	--end
	--if (isInExplosionRange(roundedPlayerPos.x, roundedPlayerPos.y)) then
	--	log("IN DANGER")
	--	local pathToSafeSpace = getPathToSafeSpace(roundedPlayerPos)
	--	log("PATH")
	--	for i,p in ipairs(pathToSafeSpace) do
	--		log(i)
	--		log(p.x)
	--		log(p.y)
	--	end
	--	if #pathToSafeSpace == 0 then
	--		return 0, 0, false, false
	--	end
	--	local f = pathToSafeSpace[1]
	--	log("first way of the path")
	--	log(f.x)
	--	log(f.y)
	--	LastTarget = {x = f.x, y = f.y}
	--	return f.x - roundedPlayerPos.x, f.y - roundedPlayerPos.y, false, false
	--else
	--	log("SAFE")
	--	local enemies = mapinfo.enemies
	--	log("len")
	--	log(#enemies)
	--	local pathToEnemy = getPathToEnemy(roundedPlayerPos, enemies)		
	--	log("b")
	--	if #pathToEnemy == 0 then
	--		return 0, 0, false, false
	--	end
	--	local f = pathToEnemy[1]
	--	log("first way of the path")
	--	log(f.x)
	--	log(f.y)
	--	log("PATH")
	--	for i, c in ipairs(pathToEnemy) do
	--		log("member")
	--		log(c.x)
	--		log(c.y)
	--	end
	--	LastTarget = {x = f.x, y = f.y}
	--	--pathfind to closest player
	--	if LastPos == nil then
	--		LastPos = {x = mapinfo.player.x, y = mapinfo.player.y}
	--	else
	--		if mapinfo.player.x == LastPos.x and mapinfo.player.y == LastPos.y then
	--			return 0, 0, false, false
	--		end
	--	end
	--	LastTarget = {x = f.x, y = f.y}
	--	return f.x - roundedPlayerPos.x, f.y - roundedPlayerPos.y, false, false;
	--end
	return 0,0, false, false
end