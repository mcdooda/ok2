local cos = math.cos
local sin = math.sin

skill {
	name     = 'pink1',
	cooldown = 0.1,
	trigger  = function(ship)
		popShipMissiles(ship, 'pink1', 1, 20, 0)
	end
}
