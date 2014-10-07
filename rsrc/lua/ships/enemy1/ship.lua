load.shipMissiles('enemy1',
	'enemy1'
)

load.shipSkills('enemy1',
	'enemy1'
)

ship {
	name       = 'enemy1',
	speed      = 250,
	health     = 50,
	experience = 10,
	texture    = 'rsrc/images/units/enemies/enemy1/texture.png',
	heightmap  = 'rsrc/images/units/enemies/enemy1/heightmap.png',
	levels     = {
		{0, 'enemy1', nil}
	},
	pop       = function(ship)
		local target = arena.getRandomPlayerShip(ALLY)
		if target then
			ship:data().targetId = target:getId()
			ship:follow(target)
		else
			ship:data().targetId = 0
		end
	end,
	update    = function(ship)
		local targetId = ship:data().targetId
		local target = arena.getEntityById(targetId)
		if target then
			ship:follow(target)
		end
	end
}
