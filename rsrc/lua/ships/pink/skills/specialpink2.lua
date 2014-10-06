local cos = math.cos
local sin = math.sin
local pi = math.pi

skill {
	name     = 'specialpink2',
	cooldown = 4,
	trigger  = function(ship)
		popShipMissiles(ship, 'pink2', 40, 20, 0, pi * 2 - pi / 20)
	end
}
