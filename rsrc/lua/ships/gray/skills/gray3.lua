local cos = math.cos
local sin = math.sin

skill {
	name     = 'gray3',
	cooldown = 0.05,
	trigger  = function(ship)
		popShipMissiles(ship, 'gray1', 1, 10, 0)
	end
}
