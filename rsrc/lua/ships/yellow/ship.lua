load.shipMissiles('yellow',
	'yellow1', 'specialyellow1'
)

load.shipSkills('yellow',
	'yellow1', 'specialyellow1',
	'yellow2', 'specialyellow2',
	'yellow3', 'specialyellow3'
)

ship {
	name      = 'yellow',
	speed     = 250,
	health    = 1,
	texture   = 'rsrc/images/units/ships/yellow/texture.png',
	heightmap = 'rsrc/images/units/ships/yellow/heightmap.png',
	bumpmap   = 'rsrc/images/units/ships/yellow/bumpmap.png',
	levels    = {
		{0, 'yellow1', 'specialyellow1'},
		{100, 'yellow2', 'specialyellow2'},
		{1000, 'yellow3', 'specialyellow3'},
	}
}
