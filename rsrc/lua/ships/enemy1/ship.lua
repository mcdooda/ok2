load.shipMissiles('enemy1',
	'enemy1'
)

load.shipSkills('enemy1',
	'enemy1'
)

ship {
	name      = 'enemy1',
	speed     = 250,
	health    = 50,
	texture   = 'rsrc/images/units/enemies/enemy1/texture.png',
	heightmap = 'rsrc/images/units/enemies/enemy1/heightmap.png',
	skills    = {
		{'enemy1', nil}
	},
	pop       = function(ship)
		local targets = arena.getShips(ALLY)
		local target = targets[math.random(1, #targets)]
		ship:data().targetId = target:getId()
		ship:follow(target)
	end,
	update    = function(ship)
		local targetId = ship:data().targetId
		local target = arena.getEntityById(targetId)
		if target then
			ship:follow(target)
		end
	end
}
