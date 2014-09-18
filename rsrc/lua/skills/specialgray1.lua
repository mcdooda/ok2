local cos = math.cos
local sin = math.sin
local pi = math.pi

skill {
	name     = 'specialgray1',
	cooldown = 3,
	trigger  = function(ship)
		popShipMissiles(ship, 'gray', 10, 20, 0, pi / 2)
	end
}
