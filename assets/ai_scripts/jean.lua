----------- JEAN

function Update()
	local Map = getMap() --
	local Danger = getDanger() --
	local player = getPlayer() --
	local playerInDanger = isInDanger() --
	local pathToClosest = getPath(player, getClosestPlayer()) --
	return x, x ,false, false
end