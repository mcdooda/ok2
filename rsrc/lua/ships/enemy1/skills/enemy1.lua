local popShipMissiles = popShipMissiles

skill {
	name     = 'enemy1',
	cooldown = 0.3,
	trigger  = function(ship, time)
		popShipMissiles(ship, 'enemy1', 1, 0, 0)
	end
}
