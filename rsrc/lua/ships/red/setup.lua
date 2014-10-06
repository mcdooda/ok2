load.ships 'red'

local popX, popY = arena.getPlayerPopPosition()

local ship1 = popShip('red', popX - 30, popY, math.pi / 2, ALLY, true)
local ship2 = popShip('red', popX + 30, popY, math.pi / 2, ALLY, true)

local function getShips()
	return ship1, ship2
end

do
	local data = ship1:data()
	data.isLeftShip = true
	data.rightShip = ship2
	data.getShips = getShips
	data.i = 1
end

do
	local data = ship2:data()
	data.isRightShip = true
	data.leftShip = ship1
	data.getShips = getShips
	data.i = -1
end


