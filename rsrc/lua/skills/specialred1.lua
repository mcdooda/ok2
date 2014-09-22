local cos = math.cos
local sin = math.sin
local pi = math.pi
local pi32 = pi / 32
local arenaHeight = arena.getHeight()

skill {
	name     = 'specialred1',
	cooldown = 1,
	trigger  = function(ship)
		local rotationZ = ship:getRotationZ()
		for i = 0, 2 do
			timer(i * 0.2, nil, function()
				do
					local x, y = ship:getAbsolutePosition(-arenaHeight, -200)
					popShip('red_specialred1', x, y, rotationZ + pi32 * (1 + i / 2))
				end
				do
					local x, y = ship:getAbsolutePosition(-arenaHeight, 200)
					popShip('red_specialred1', x, y, rotationZ - pi32 * (1 + i / 2))
				end
			end)
		end
	end
}
