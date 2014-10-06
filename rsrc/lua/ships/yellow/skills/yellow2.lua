local cos = math.cos
local sin = math.sin
local pi24 = math.pi / 24

skill {
	name     = 'yellow2',
	cooldown = 0.2,
	trigger  = function(ship)
		popShipMissiles(ship, 'yellow1', 4, 20, 0, pi24)
	end
}
