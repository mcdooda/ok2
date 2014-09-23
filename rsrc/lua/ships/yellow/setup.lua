load.ships 'yellow'

local minX, minY, maxX, maxY = arena.getBounds()

popShip('yellow', 0, minY / 2, math.pi / 2, ALLY, true)
