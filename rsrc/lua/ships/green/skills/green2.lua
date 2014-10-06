local cos = math.cos
local sin = math.sin

skill {
	name     = 'green2',
	cooldown = 0.12,
	trigger  = function(ship)
		popShipMissiles(ship, 'green1', 2, 0, 40)
	end
}
