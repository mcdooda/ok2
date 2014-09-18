local cos = math.cos
local sin = math.sin
local pi = math.pi

skill {
	name     = 'red1',
	cooldown = 0.2,
	trigger  = function(ship)
		popShipMissiles(ship, 'red', 2, 0, 30, -pi / 48)
	end
}
