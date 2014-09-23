load.ships 'red'

local minX, minY, maxX, maxY = arena.getBounds()

popShip('red', 0, minY / 2, math.pi / 2, ALLY, true)
