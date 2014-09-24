local cos = math.cos
local sin = math.sin
local pi = math.pi
local pi32 = pi / 32
local dx = -arena.getHeight() * 1.2

skill {
	name     = 'specialred1',
	cooldown = 1,
	trigger  = function(ship)
		local rotationZ = ship:getRotationZ()
		local side = ship:getSide()
		for i = 0, 2 do
			timer(i * 0.2, nil, function()
				do
					local x, y = ship:getAbsolutePosition(dx, -200)
					popShip('red_specialred1', x, y, rotationZ + pi32 * (1 + i / 2), side)
				end
				do
					local x, y = ship:getAbsolutePosition(dx, 200)
					popShip('red_specialred1', x, y, rotationZ - pi32 * (1 + i / 2), side)
				end
			end)
		end
	end
}
