local cos = math.cos
local sin = math.sin

skill {
	name     = 'pink',
	cooldown = 0.2,
	trigger  = function(ship)
		--[[local rotation = ship:getRotationZ();
		local x, y = ship:getPosition()
		fireMissile('blue', x + cos(rotation) * 20, y + sin(rotation) * 20)
		]]
		print 'PINK SKILL'
	end
}
