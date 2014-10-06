local cos = math.cos
local sin = math.sin

skill {
	name     = 'pink3',
	cooldown = 0.04,
	trigger  = function(ship)
		popShipMissiles(ship, 'pink3', 1, 20, 0)
	end
}
