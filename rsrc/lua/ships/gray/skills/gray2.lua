local cos = math.cos
local sin = math.sin

skill {
	name     = 'gray2',
	cooldown = 0.10,
	trigger  = function(ship)
		popShipMissiles(ship, 'gray1', 1, 10, 0)
	end
}
