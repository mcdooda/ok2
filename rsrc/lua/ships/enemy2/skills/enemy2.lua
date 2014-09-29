local popShipMissiles = popShipMissiles

skill {
	name     = 'enemy2',
	cooldown = 0.3,
	trigger  = function(ship, time)
		popShipMissiles(ship, 'enemy2', 1, 0, 0)
	end
}
