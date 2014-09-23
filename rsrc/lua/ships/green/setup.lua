load.ships 'green'

local minX, minY, maxX, maxY = arena.getBounds()

popShip('green', 0, minY / 2, math.pi / 2, ALLY, true)
