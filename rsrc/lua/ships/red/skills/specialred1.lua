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
		do
			local x, y = ship:getAbsolutePosition(dx, 0)
			popShip('red_specialred1', x, y, rotationZ, side)
		end
	end
}
