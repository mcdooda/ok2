load.shipMissiles('pink',
	'pink1',
	'pink2',
	'pink3'
)

load.shipSkills('pink',
	'pink1', 'specialpink1',
	'pink2', 'specialpink2',
	'pink3', 'specialpink3'
)

ship {
	name      = 'pink',
	speed     = 350,
	health    = 1,
	texture   = 'rsrc/images/units/ships/pink/texture.png',
	heightmap = 'rsrc/images/units/ships/pink/heightmap.png',
	bumpmap   = 'rsrc/images/units/ships/pink/bumpmap.png',
	levels    = {
		{0, 'pink1', 'specialpink1'},
		{100, 'pink2', 'specialpink2'},
		{1000, 'pink3', 'specialpink3'}
	}
}
