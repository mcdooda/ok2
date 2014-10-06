local cos = math.cos
local sin = math.sin
local pi = math.pi

skill {
	name     = 'specialpink3',
	cooldown = 3,
	trigger  = function(ship)
		popShipMissiles(ship, 'pink3', 80, 20, 0, pi * 2 - pi / 40)
	end
}
