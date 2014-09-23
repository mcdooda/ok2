load.shipMissiles('gray',
	'gray1'
)

load.shipSkills('gray',
	'gray1',
	'specialgray1'
)

ship {
	name      = 'gray',
	speed     = 450,
	texture   = 'rsrc/images/units/ships/gray/texture.png',
	heightmap = 'rsrc/images/units/ships/gray/heightmap.png',
	bumpmap   = 'rsrc/images/units/ships/gray/bumpmap.png',
	skills    = {
		{'gray1', 'specialgray1'}
	}
}