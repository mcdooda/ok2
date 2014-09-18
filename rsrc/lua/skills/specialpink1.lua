local cos = math.cos
local sin = math.sin
local pi = math.pi

skill {
	name     = 'specialpink1',
	cooldown = 5,
	trigger  = function(ship)
		popShipMissiles(ship, 'pink', 20, 20, 0, pi * 2 - pi / 10)
	end
}
