load.ships 'gray'

local minX, minY, maxX, maxY = arena.getBounds()

popShip('gray', 0, minY / 2, math.pi / 2, ALLY, true)
