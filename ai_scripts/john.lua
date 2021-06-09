function Update(player, infos, players)
	print(player.x);
	print(player.y);
	print(player.z);
	for i, info in ipairs(infos) do
		--print("x");
		--print (info.x);
		--print("y");
		--print (info.y);
		--print("z");
		--print (info.z);
		--print("type");
		--print (info.type);
	  end
	return 1, 1, false, false;
end