function Sum(a,b)
	return a + b;
end

function Update(infos)
	for i, info in ipairs(infos) do
		print (info.x);
		print (info.y);
		print (info.z);
		print (info.type);
	  end
	return 1, 1, false, false;
	--return info.x, info.y, (info.z ~= 1), (info.type ~= 0);
end