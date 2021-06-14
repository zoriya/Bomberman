math.randomseed(os.time())

function Update(player, infos, players)
	return (math.random() < 0.5), (math.random() < 0.5), false, false;
end