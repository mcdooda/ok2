load.shipMissiles('enemy3',
	'enemy3'
)

load.shipSkills('enemy3',
	'enemy3'
)

local pi16 = math.pi / 16

ship {
	name      = 'enemy3',
	speed     = 200,
	health    = 150,
	texture   = 'rsrc/images/units/enemies/enemy3/texture.png',
	heightmap = 'rsrc/images/units/enemies/enemy3/heightmap.png',
	skills    = {
		{'enemy3', nil}
	},
	pop       = function(ship)
		local data = ship:data()
		data.rzSpeed = 0
		data.popInterval = 1
	end,
	update    = function(ship, time, dt)
		local data = ship:data()
		local rz = ship:getRotationZ()
		ship:setRotationZ(rz + data.rzSpeed * dt)
		if time > ship:getPopTime() + data.popInterval then
			if not data.pop then
				local x, y = ship:getPosition()
				do
					local ship1 = popShip('enemy3', x, y, rz, ship:getSide())
					local data1 = ship1:data()
					data1.rzSpeed = -0.3
					data1.pop = true
				end
				do
					local ship2 = popShip('enemy3', x, y, rz, ship:getSide())
					local data2 = ship2:data()
					data2.rzSpeed = 0.3
					data2.pop = true
				end
				data.pop = true
			end
			data.rzSpeed = 0
		end
	end,
}
