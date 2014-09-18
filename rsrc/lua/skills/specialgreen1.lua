local cos = math.cos
local sin = math.sin
local pi = math.pi
local pi48 = pi / 48

skill {
	name     = 'specialgreen1',
	cooldown = 2,
	trigger  = function(ship)
		popShipMissiles(ship, 'green', 10, 0, 40, pi48)
	end
}
