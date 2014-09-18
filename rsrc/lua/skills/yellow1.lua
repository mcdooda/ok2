local cos = math.cos
local sin = math.sin

skill {
	name     = 'yellow1',
	cooldown = 0.2,
	trigger  = function(ship)
		popShipMissiles(ship, 'yellow', 1, 20, 0)
	end
}
