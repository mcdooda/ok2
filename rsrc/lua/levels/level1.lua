local yield = coroutine.yield
local pi = math.pi

local function wait(d)
	local t = getTime() + d
	repeat
		yield()
	until getTime() >= t
end

local arenaMinX, arenaMinY, arenaMaxX, arenaMaxY = arena.getBounds()

yield()

do
	popShip('red_specialred1', -100, arenaMaxY + 100, -pi / 2, ENEMY)
	wait(1)
	popShip('red_specialred1', 100, arenaMaxY + 100, -pi / 2, ENEMY)
end
