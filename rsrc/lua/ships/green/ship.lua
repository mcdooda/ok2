load.shipMissiles('green',
	'green1'
)

load.shipSkills('green',
	'green1', 'specialgreen1'
)

ship {
	name      = 'green',
	speed     = 400,
	health    = 1,
	texture   = 'rsrc/images/units/ships/green/texture.png',
	heightmap = 'rsrc/images/units/ships/green/heightmap.png',
	bumpmap   = 'rsrc/images/units/ships/green/bumpmap.png',
	levels    = {
		{0, 'green1', 'specialgreen1'}
	}
}
