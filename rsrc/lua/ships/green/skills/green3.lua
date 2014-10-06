local cos = math.cos
local sin = math.sin

skill {
	name     = 'green3',
	cooldown = 0.06,
	trigger  = function(ship)
		popShipMissiles(ship, 'green1', 2, 0, 40)
	end
}
