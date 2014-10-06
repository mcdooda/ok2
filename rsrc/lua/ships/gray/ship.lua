load.shipMissiles('gray',
	'gray1'
)

load.shipSkills('gray',
	'gray1', 'specialgray1',
	'gray2', 'specialgray2',
	'gray3', 'specialgray3'
)

ship {
	name      = 'gray',
	speed     = 450,
	health    = 1,
	texture   = 'rsrc/images/units/ships/gray/texture.png',
	heightmap = 'rsrc/images/units/ships/gray/heightmap.png',
	bumpmap   = 'rsrc/images/units/ships/gray/bumpmap.png',
	levels    = {
		{0, 'gray1', 'specialgray1'},
		{100, 'gray2', 'specialgray2'},
		{1000, 'gray3', 'specialgray3'}
	}
}
