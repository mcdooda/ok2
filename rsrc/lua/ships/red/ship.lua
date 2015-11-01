load.shipMissiles('red',
	'red1'
)

load.shipSkills('red',
	'red1', 'specialred1',
	'red2', 'specialred2',
	'red3', 'specialred3'
)

load.shipShips('red',
	'red_specialred1'
)

local dx = 60

ship {
	name      = 'red',
	speed     = 600,
	health    = 1,
	texture   = 'rsrc/images/units/ships/red/texture.png',
	heightmap = 'rsrc/images/units/ships/red/heightmap.png',
	bumpmap   = 'rsrc/images/units/ships/red/bumpmap.png',
	levels    = {
		{0, 'red1', 'specialred1'},
		{100, 'red2', 'specialred2'},
		{500, 'red3', 'specialred3'}
	},
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
					if leftShip:getNumLives() > 0 then
						rightShip:setPositionX(lx + dx)
					end
				else
					if rightShip:getNumLives() > 0 then
						leftShip:setPositionX(rx - dx)
					end
				end
			end
		end
	end
}
