local cos = math.cos
local sin = math.sin
local pi24 = math.pi / 24

skill {
	name     = 'yellow1',
	cooldown = 0.2,
	trigger  = function(ship)
		popShipMissiles(ship, 'yellow1', 2, 20, 0, pi24)
	end
}
