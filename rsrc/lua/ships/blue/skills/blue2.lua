local popShipMissiles = popShipMissiles

skill {
	name     = 'blue2',
	cooldown = 0.1,
	trigger  = function(ship, time)
		popShipMissiles(ship, 'blue1', 2, 2, 28)
	end
}
