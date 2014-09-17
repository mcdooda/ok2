local cos = math.cos
local sin = math.sin
local pi = math.pi

skill {
	name     = 'blue',
	cooldown = 1,
	trigger  = function(ship)
		popMissile('blue', 0, 0, pi / 2)
		--popShip('blue', 0, 0, pi / 2)
		print 'BLUE SKILL'
	end
}
