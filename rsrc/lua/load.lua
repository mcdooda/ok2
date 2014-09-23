local load = {}

function load.ships(...)
	for i = 1, select('#', ...) do
		local shipName = select(i, ...)
		dofile('rsrc/lua/ships/' .. shipName .. '/ship.lua')
	end
end

function load.shipSkills(shipName, ...)
	for i = 1, select('#', ...) do
		local skillName = select(i, ...)
		dofile('rsrc/lua/ships/' .. shipName .. '/skills/' .. skillName .. '.lua')
	end
end

function load.shipMissiles(shipName, ...)
	for i = 1, select('#', ...) do
		local missileName = select(i, ...)
		dofile('rsrc/lua/ships/' .. shipName .. '/missiles/' .. missileName .. '.lua')
	end
end

function load.shipShips(shipName, ...)
	for i = 1, select('#', ...) do
		local subShipName = select(i, ...)
		dofile('rsrc/lua/ships/' .. shipName .. '/ships/' .. subShipName .. '.lua')
	end
end

return load
