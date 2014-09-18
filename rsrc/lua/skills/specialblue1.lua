local cos = math.cos
local sin = math.sin
local pi = math.pi
local popShipMissiles = popShipMissiles

skill {
	name     = 'specialblue1',
	cooldown = 3,
	trigger  = function(ship)
		popShipMissiles(ship, 'specialblue1', 20, 18, 30, pi)
	end
}
