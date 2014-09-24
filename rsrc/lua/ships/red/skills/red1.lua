local cos = math.cos
local sin = math.sin
local mpi64 = -math.pi / 64

skill {
	name     = 'red1',
	cooldown = 0.3,
	trigger  = function(ship)
		popShipMissiles(ship, 'red1', 2, 0, 30, mpi64)
	end
}
