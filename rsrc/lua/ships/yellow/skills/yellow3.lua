local cos = math.cos
local sin = math.sin
local pi24 = math.pi / 24

skill {
	name     = 'yellow3',
	cooldown = 0.2,
	trigger  = function(ship)
		popShipMissiles(ship, 'yellow1', 6, 20, 0, pi24)
	end
}
