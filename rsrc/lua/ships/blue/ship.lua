load.shipMissiles('blue',
	'blue1',
	'specialblue1'
)

load.shipSkills('blue',
	'blue1',
	'specialblue1'
)

ship {
	name      = 'blue',
	speed     = 500,
	health    = 100,
	texture   = 'rsrc/images/units/ships/blue/texture.png',
	heightmap = 'rsrc/images/units/ships/blue/heightmap.png',
	bumpmap   = 'rsrc/images/units/ships/blue/bumpmap.png',
	skills    = {
		{'blue1', 'specialblue1'}
	}
}
