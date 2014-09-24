load.ships 'red'

local minX, minY, maxX, maxY = arena.getBounds()

local ship1 = popShip('red', -30, minY / 2, math.pi / 2, ALLY, true)
local ship2 = popShip('red',  30, minY / 2, math.pi / 2, ALLY, true)

local function getShips()
	return ship1, ship2
end

do
	local data = ship1:data()
	data.isLeftShip = true
	data.rightShip = ship2
	data.getShips = getShips
end

do
	local data = ship2:data()
	data.isRightShip = true
	data.leftShip = ship1
	data.getShips = getShips
end


