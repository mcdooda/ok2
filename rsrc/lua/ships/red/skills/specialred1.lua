local dx = -arena.getHeight() * 1.2

skill {
	name     = 'specialred1',
	cooldown = 2,
	trigger  = function(ship)
		local rotationZ = ship:getRotationZ()
		local side = ship:getSide()
		local di = ship:data().i
		do
			local x, y = ship:getAbsolutePosition(dx, 60 * di)
			popShip('red_specialred1', x, y, rotationZ, side)
		end
	end
}
