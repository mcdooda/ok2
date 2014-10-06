load.shipMissiles('green',
	'green1'
)

load.shipSkills('green',
	'green1', 'specialgreen1',
	'green2', 'specialgreen2',
	'green3', 'specialgreen3'
)

ship {
	name      = 'green',
	speed     = 400,
	health    = 1,
	texture   = 'rsrc/images/units/ships/green/texture.png',
	heightmap = 'rsrc/images/units/ships/green/heightmap.png',
	bumpmap   = 'rsrc/images/units/ships/green/bumpmap.png',
	levels    = {
		{0, 'green1', 'specialgreen1'},
		{100, 'green2', 'specialgreen2'},
		{1000, 'green3', 'specialgreen3'}
	}
}
