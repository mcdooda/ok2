missile {
	name    = 'yellow1',
	speed   = 1000,
	damage  = 25,
	texture = 'rsrc/images/missiles/special3.png',
	update  = function(missile, time, dt)
		local rz = 0.15
		if missile:data().i % 2 == 0 then
			rz = -0.15
		end
		missile:setRotationZ(missile:getRotationZ() + rz * dt)
	end
}
