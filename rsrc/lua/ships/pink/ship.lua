load.shipMissiles('pink',
	'pink1'
)

load.shipSkills('pink',
	'pink1', 'specialpink1'
)

ship {
	name      = 'pink',
	speed     = 350,
	health    = 1,
	texture   = 'rsrc/images/units/ships/pink/texture.png',
	heightmap = 'rsrc/images/units/ships/pink/heightmap.png',
	bumpmap   = 'rsrc/images/units/ships/pink/bumpmap.png',
	levels    = {
		{0, 'pink1', 'specialpink1'}
	}
}
