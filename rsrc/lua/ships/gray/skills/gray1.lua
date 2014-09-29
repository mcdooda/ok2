local cos = math.cos
local sin = math.sin

skill {
	name     = 'gray1',
	cooldown = 0.15,
	trigger  = function(ship)
		popShipMissiles(ship, 'gray1', 1, 10, 0)
	end
}
