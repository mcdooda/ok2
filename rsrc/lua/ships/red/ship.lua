load.shipMissiles('red',
	'red1'
)

load.shipSkills('red',
	'red1', 'specialred1'
)

load.shipShips('red',
	'red_specialred1'
)

local dx = 60

ship {
	name      = 'red',
	speed     = 300,
	health    = 1,
	texture   = 'rsrc/images/units/ships/red/texture.png',
	heightmap = 'rsrc/images/units/ships/red/heightmap.png',
	bumpmap   = 'rsrc/images/units/ships/red/bumpmap.png',
	update    = function(ship)
		local data = ship:data()
		if data.isLeftShip or data.isRightShip then
			local leftShip, rightShip = data.getShips()
			local rx = rightShip:getPositionX()
			local lx = leftShip:getPositionX()
			local distance = rx - lx
			if distance < dx then
				local cx = (rx + lx) / 2
				if cx < 0 then
					rightShip:setPositionX(lx + dx)
				else
					leftShip:setPositionX(rx - dx)
				end
			end
		end
	end,
	skills    = {
		{'red1', 'specialred1'}
	}
}
