load.shipMissiles('red',
	'red1'
)

load.shipSkills('red',
	'red1',
	'specialred1'
)

load.shipShips('red',
	'red_specialred1'
)

ship {
	name      = 'red',
	speed     = 300,
	texture   = 'rsrc/images/units/ships/red/texture.png',
	heightmap = 'rsrc/images/units/ships/red/heightmap.png',
	bumpmap   = 'rsrc/images/units/ships/red/bumpmap.png',
	skills    = {
		{'red1', 'specialred1'}
	}
}
