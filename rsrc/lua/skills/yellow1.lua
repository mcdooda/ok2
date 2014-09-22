local cos = math.cos
local sin = math.sin
local pi48 = math.pi / 48

skill {
	name     = 'yellow1',
	cooldown = 0.2,
	trigger  = function(ship)
		popShipMissiles(ship, 'yellow', 2, 20, 0, pi48)
	end
}
