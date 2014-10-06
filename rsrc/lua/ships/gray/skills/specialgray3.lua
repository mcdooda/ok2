local cos = math.cos
local sin = math.sin
local pi = math.pi
local pi2 = pi / 2
local pi8 = pi / 8

skill {
	name     = 'specialgray3',
	cooldown = 3,
	trigger  = function(ship)
		local data = ship:data()
		data.i = ((data.i or 0) + 1) % 2
		local angle = pi2
		if data.i % 2 == 0 then
			angle = pi8
		end
		popShipMissiles(ship, 'gray1', 30, 20, 0, angle)
	end
}
