math.randomseed(os.time())

function Update(mapinfo)

	local x = math.random()
	local y = math.random()
	if (math.random() < 0.5) then
		x = x * -1
	end
	if (math.random() < 0.5) then
		y = y * -1
	end
	return x, y, false, true;
end