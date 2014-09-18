local cos = math.cos
local sin = math.sin

skill {
	name     = 'green1',
	cooldown = 0.2,
	trigger  = function(ship)
		popShipMissiles(ship, 'green', 2, 0, 40)
	end
}
