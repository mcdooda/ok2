local cos = math.cos
local sin = math.sin
local pi = math.pi

skill {
	name     = 'blue',
	cooldown = 0.05,
	trigger  = function(ship)
		popShipMissiles(ship, 'blue', 2, 18, 30, pi / 8)
		popShipMissiles(ship, 'blue', 2, 18, 30, -pi / 8)
		popShipMissiles(ship, 'blue', 2, 18, 30)
	end
}
