local mpi = -math.pi
local mpi32 = mpi / 32
local mpi64 = mpi / 64

skill {
	name     = 'red2',
	cooldown = 0.25,
	trigger  = function(ship)
		popShipMissiles(ship, 'red1', 2, 0, 30, mpi32)
		popShipMissiles(ship, 'red1', 2, 0, 30, mpi64)
	end
}
