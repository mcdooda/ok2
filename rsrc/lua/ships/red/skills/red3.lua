local mpi = -math.pi
local mpi16 = mpi / 16
local mpi32 = mpi / 32
local mpi64 = mpi / 64

skill {
	name     = 'red3',
	cooldown = 0.2,
	trigger  = function(ship)
		popShipMissiles(ship, 'red1', 2, 0, 30, mpi16)
		popShipMissiles(ship, 'red1', 2, 0, 30, mpi32)
		popShipMissiles(ship, 'red1', 2, 0, 30, mpi64)
	end
}
