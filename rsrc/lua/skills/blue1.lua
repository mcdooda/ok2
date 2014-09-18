local cos = math.cos
local sin = math.sin
local pi = math.pi
local popShipMissiles = popShipMissiles

skill {
	name     = 'blue1',
	cooldown = 0.15,
	trigger  = function(ship)
		popShipMissiles(ship, 'blue1', 2, 18, 30)
	end
}
