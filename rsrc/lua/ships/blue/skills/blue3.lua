local popShipMissiles = popShipMissiles
local pi = math.pi
local pi64 = pi / 64
local mpi64 = -pi64

skill {
	name     = 'blue3',
	cooldown = 0.1,
	trigger  = function(ship, time)
		popShipMissiles(ship, 'blue1', 2, 2, 28, pi64)
		popShipMissiles(ship, 'blue1', 2, 2, 28, mpi64)
	end
}
