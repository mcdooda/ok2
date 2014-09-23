load.ships 'blue'

local minX, minY, maxX, maxY = arena.getBounds()

popShip('blue', 0, minY / 2, math.pi / 2, ALLY, true)
