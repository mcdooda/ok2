local yield = coroutine.yield
local pi = math.pi

local function wait(d)
	local t = getTime() + d
	repeat
		yield()
	until getTime() >= t
end

local arenaMinX, arenaMinY, arenaMaxX, arenaMaxY = arena.getBounds()

load.ships 'pink'

yield()

popShip('pink', 0, arenaMaxY, -pi / 2, ENEMY)
