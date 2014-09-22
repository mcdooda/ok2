local cos = math.cos
local sin = math.sin
local mpi48 = -math.pi / 48

skill {
	name     = 'red1',
	cooldown = 0.2,
	trigger  = function(ship)
		popShipMissiles(ship, 'red', 2, 0, 30, mpi48)
	end
}
