local cos = math.cos
local sin = math.sin

skill {
	name     = 'pink2',
	cooldown = 0.07,
	trigger  = function(ship)
		popShipMissiles(ship, 'pink2', 1, 20, 0)
	end
}
