local cos = math.cos
local sin = math.sin
local pi = math.pi
local popShipMissiles = popShipMissiles

skill {
	name     = 'specialblue1',
	cooldown = 3,
	trigger  = function(ship)
		local sx = ship:getSpeed()
		if sx < 0 then
			timer(0.5, function(t)
				ship:setRotationZ(t:getProgression() * pi * 2 + pi / 2)
			end)
		elseif sx > 0 then
			timer(0.5, function(t)
				ship:setRotationZ(-t:getProgression() * pi * 2 + pi / 2)
			end)
		end
		popShipMissiles(ship, 'specialblue1', 20, 18, 30, pi)
	end
}
