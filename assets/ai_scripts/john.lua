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

function getPathToSafeSpace(player)
	local res = getClosestSafeSpace()
	log("run to")
	log(res.x)
	log(res.y)
	
	local p = {player}
	table.insert(p, res)
	return p
end

function getClosestEnemy(player, enemies)
	local dist = -1
	local enemyFound = nil
	for i, enemy in ipairs(enemies) do
		local tmp =  math.sqrt(math.pow(enemy.x - player.x, 2) + math.pow(enemy.y - player.y, 2))
		if (dist == -1 or dist > tmp) then
			dist = tmp
			enemyFound = enemy
		end
	end
	return enemyFound
end

function canKillTarget(player, target)
	if math.sqrt(math.pow(target.x - player.x, 2) + math.pow(target.y - player.y, 2)) <= getRadius() and (target.x == player.x or target.y == player.y) then
		return true
	end
	return false
end

LastTarget = nil
------ Update

math.randomseed(os.time())
function Update()
	log("NEW FRAME")
	local enemies = getEnemies()
	local player = getPlayerRound()
	local playerNotRound = getPlayer()
	local enemy = getClosestEnemy(player, getEnemiesRound())
	if LastTarget ~= nil then
		log("last target")
		log(LastTarget.x)
		log(LastTarget.y)
		if math.abs(LastTarget.x - playerNotRound.x) <= 0.1 and math.abs(LastTarget.x - playerNotRound.x) <= 0.1 then
			LastTarget = nil
		else
			return (LastTarget.x - playerNotRound.x), (LastTarget.y - playerNotRound.y), false, false
		end
	end
	local rnd = math.random(10)
	if rnd == 10 then
		local x = math.random(4)
		local dirX = {-1, 0, 1, 0}
		local dirY = {0, -1, 0, 1}
		local target = {x = player.x + dirX[x], y = player.y + dirY[x]}
		log("target")
		log(target.x)
		log(target.y)
		if target.x < 0 or target.x > 16 or target.y < 0 or target.y > 16 then
			return 0, 0, false, false
		end
		local blocktypetarget = getBlockType(target.x, target.y)
		local dangerleveltarget = getDangerLevel(target.x, target.y)
		log("blocktype")
		log(blocktypetarget)
		log("dangelever")
		log(dangerleveltarget)
		if dangerleveltarget == 0 and blocktypetarget == 0 then
			log("a")
			LastTarget = {x = target.x, y = target.y}
			return  LastTarget.x - player.x, LastTarget.y - player.y, false, false
		end
	end
	log("player Info")
	log(playerNotRound.x)
	log(playerNotRound.y)
	log("End player Info")
	if getDangerLevelPlayer() then
		log("INDANGER")
		local dangerMap = getDanger()
		PrintMap(dangerMap, 17, 17)
		local path = getPathToSafeSpace(player)
		if #path >= 2 then
			log("path found")
			for i, c in ipairs(path) do
				log(i)
				log(c.x)
				log(c.y)
			end
			LastTarget = {x = path[2].x, y = path[2].y}
			return path[2].x - player.x, path[2].y - player.y, false, false
		end
		log("nopath found")
		return 0, 0, false, false
	end
	log("Fnc Path")
	log(enemy.x)
	log(enemy.y)
	log("player path fnc")
	log(player.x)
	log(player.y)
	if player.x <= 0 then
		player.x = 0
	end
	if player.y <= 0 then
		player.y = 0
	end
	if enemy.x <= 0 then
		enemy.x = 0
	end
	if enemy.y <= 0 then
		enemy.y = 0
	end
	local path = getPath(player.x, player.y, enemy.x, enemy.y, true)
	log("End Fnc Path")
	log("Path")
	for i, p in ipairs(path) do
		log("Node")
		log(p.x)
		log(p.y)
	end
	log("End path")
	if canKillTarget(player, enemy) then
		LastTarget = nil
		return 0, 0, true, true
	end
	local target = path[2]
	if getBlockType(target.x, target.y) == 1 then		
		local canPut = canPutBombSafe()
		if canPut then
			LastTarget = nil
			return 0, 0, true, true
		else
			return 0, 0, false, false
		end
	end
	if #path <= 1 then
		return 0, 0, true, true
	end
	local blocktypetarget = getBlockType(target.x, target.y)
	local dangerleveltarget = getDangerLevel(target.x, target.y)
	log("blocktype")
	log(blocktypetarget)
	log("dangelever")
	log(dangerleveltarget)
	if dangerleveltarget == 0 and blocktypetarget == 0 then
		log("a")
		LastTarget = {x = target.x, y = target.y}
		return  LastTarget.x - player.x, LastTarget.y - player.y, false, false
	end
	return 0,0, false, false
end