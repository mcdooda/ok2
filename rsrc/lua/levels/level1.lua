local yield = coroutine.yield
local pi = math.pi
local pi2 = pi / 2
local mpi2 = -pi2
local pi16 = pi / 16

local function wait(d)
	local t = getTime() + d
	repeat
		yield()
	until getTime() >= t
end

local function waitUntilNoEnemy()
	while arena.getNumShips(ENEMY) > 0 do
		yield()
	end
end

local arenaMinX, arenaMinY, arenaMaxX, arenaMaxY = arena.getBounds()
local popY = arenaMaxY + 100

local function popLine(shipName, minX, maxX, count, rotationZ)
	for i = 1, count do
		local x = minX + (maxX - minX) * (i - 1) / (count - 1)
		popShip(shipName, x, popY, rotationZ, ENEMY)
	end
end

-- LOAD SHIPS
load.ships(
	'enemy1',
	'enemy2',
	'enemy3'
)

-- BIG YIELD
yield()
-- BIG YIELD

-- ENEMY 1

for i = 2, 6 do
	popLine('enemy1', arenaMinX / 2, arenaMaxX / 2, i, mpi2)
	i = i + 1
	waitUntilNoEnemy()
end

-- ENEMY 2

for i = 2, 6 do
	popLine('enemy2', arenaMinX / 2, arenaMaxX / 2, i, mpi2 - pi16)
	waitUntilNoEnemy()
	popLine('enemy2', arenaMinX / 2, arenaMaxX / 2, i, mpi2 + pi16)
	waitUntilNoEnemy()
	popLine('enemy2', arenaMinX / 2, arenaMaxX / 2, i, mpi2)
	waitUntilNoEnemy()
end

-- ENEMY 3

for i = 1, 5 do
	local x
	if i % 2 == 0 then
		x = arenaMinX / 2
	else
		x = arenaMaxX / 2
	end
	popShip('enemy3', x, popY, mpi2, ENEMY):data().popInterval = (6 - i) / 2
	waitUntilNoEnemy()
end



