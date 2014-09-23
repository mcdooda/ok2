local cos = math.cos
local sin = math.sin
local pi = math.pi
local popShipMissiles = popShipMissiles

skill {
	name     = 'blue1',
	cooldown = 0.1,
	trigger  = function(ship, time)
		local data = ship:data()
		data.i = ((data.i or 0) + 1) % 2
		if data.i % 2 == 0 then
			popShipMissiles(ship, 'blue1', 1, 2, 14)
		else
			popShipMissiles(ship, 'blue1', 1, 2, -14)
		end
	end
}
