load.ships 'pink'

local minX, minY, maxX, maxY = arena.getBounds()

popShip('pink', 0, minY / 2, math.pi / 2, ALLY, true)
