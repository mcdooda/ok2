load.shipMissiles('yellow',
	'yellow1'
)

load.shipSkills('yellow',
	'yellow1',
	'specialyellow1'
)

ship {
	name      = 'yellow',
	speed     = 250,
	health    = 100,
	texture   = 'rsrc/images/units/ships/yellow/texture.png',
	heightmap = 'rsrc/images/units/ships/yellow/heightmap.png',
	bumpmap   = 'rsrc/images/units/ships/yellow/bumpmap.png',
	skills    = {
		{'yellow1', 'specialyellow1'}
	}
}
