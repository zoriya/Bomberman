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

function dist(nodeA, nodeB)
	return math.sqrt(math.pow(nodeB.x - nodeA.x, 2) + math.pow(nodeB.y - nodeA.y, 2))
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



function getPathToSafeSpace(player)
	local res = getClosestSafeSpace()
	print("run to")
	print(res.x)
	print(res.y)
	
	local p = {player}
	table.insert(p, res)
	return p
end

LastTarget = nil
------ Update
function Update()
	log("NEW FRAME")
	--local path = getPath(0, 0, 16, 16);
	
	local player = getPlayer()
	if LastTarget ~= nil then
		log("last target")
		log(LastTarget.x)
		log(LastTarget.y)
		if math.abs(LastTarget.x - player.x) <= 0.1 and math.abs(LastTarget.x - player.x) <= 0.1 then
			LastTarget = nil
		else
			return (LastTarget.x - player.x), (LastTarget.y - player.y), false, false
		end
	end
	
	print("player")
	print(player.x)
	print(player.y)
	local player = getPlayerRound();
	if getDangerLevelPlayer() then
		print("INDANGER")
		local dangerMap = getDanger()
		PrintMap(dangerMap, 17, 17)
		local path = getPathToSafeSpace(player)
		if #path >= 2 then
			print("path found")
			for i, c in ipairs(path) do
				print(i)
				print(c.x)
				print(c.y)
			end
			LastTarget = {x = path[2].x, y = path[2].y}
			return path[2].x - player.x, path[2].y - player.y, false, false
		end
		print("nopath found")
		return 0, 0, false, false
	end
	if canPutBombSafe() then
		return 0, 0, true, true
	end
	return 0,0, false, false
end