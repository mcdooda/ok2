local sin = math.sin

missile {
	name    = 'specialblue1',
	speed   = 1500,
	texture = 'rsrc/images/missiles/missile1.png',
	pop     = function(self, time)
		print 'POP'
		local data = self:data()
		data.popTime = time
		data.popRotationZ = self:getRotationZ()
	end,
	update  = function(self, time, dt)
		local data = self:data()
		self:setRotationZ(data.popRotationZ + sin(time - data.popTime))
	end
}
