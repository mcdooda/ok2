local popShipMissiles = popShipMissiles

skill {
	name     = 'enemy3',
	cooldown = 0.3,
	trigger  = function(ship, time)
		popShipMissiles(ship, 'enemy3', 1, 0, 0)
	end
}
