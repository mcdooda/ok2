local sin = math.sin

missile {
	name    = 'specialblue3',
	speed   = 1000,
	damage  = 25,
	texture = 'rsrc/images/missiles/missile1.png',
	pop     = function(self, time)
		local data = self:data()
		data.popTime = time
		data.popRotationZ = self:getRotationZ()
	end,
	update  = function(self, time, dt)
		local data = self:data()
		self:setRotationZ(data.popRotationZ + sin(time * 20 - data.popTime))
	end
}
