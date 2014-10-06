load.shipMissiles('blue',
	'blue1', 'specialblue1',
	         'specialblue2',
	         'specialblue3'
)

load.shipSkills('blue',
	'blue1', 'specialblue1',
	'blue2', 'specialblue2',
	'blue3', 'specialblue3'
)

ship {
	name      = 'blue',
	speed     = 500,
	health    = 1,
	texture   = 'rsrc/images/units/ships/blue/texture.png',
	heightmap = 'rsrc/images/units/ships/blue/heightmap.png',
	bumpmap   = 'rsrc/images/units/ships/blue/bumpmap.png',
	levels    = {
		{0, 'blue1', 'specialblue1'},
		{100, 'blue2', 'specialblue2'},
		{1000, 'blue3', 'specialblue3'}
	}
}
