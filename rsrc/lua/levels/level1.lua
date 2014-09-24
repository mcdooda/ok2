local yield = coroutine.yield
local pi = math.pi

local function wait(d)
	local t = getTime() + d
	repeat
		yield()
	until getTime() >= t
end

local arenaMinX, arenaMinY, arenaMaxX, arenaMaxY = arena.getBounds()

load.ships 'red'

yield()

--[[
do
	local top = arenaMaxY + 100
	local left = arenaMinX * 9 / 10
	local right = arenaMaxX * 9 / 10
	local count = 10
	
	for i = 1, 100 do
	
		for i = 1, count do
			popShip('red_specialred1', left + (i - 1) / (count - 1) * (right - left), top, -pi / 2, ENEMY)
			wait(0.1)
		end
	
		for i = count, 1, -1 do
			popShip('red_specialred1', left + (i - 1) / (count - 1) * (right - left), top, -pi / 2, ENEMY)
			wait(0.1)
		end
		
	end
end
]]


local bottom = arenaMinY * 9 / 10
local top = arenaMaxY * 9 / 10
local left = arenaMinX * 9 / 10
local right = arenaMaxX * 9 / 10
local count = 6

for i = 1, count do
	for j = 1, count do
		popShip('red_specialred1', left + (i - 1) / (count - 1) * (right - left), bottom + (j - 1) / (count - 1) * (top - bottom), -pi / 2, ENEMY)
	end
end

