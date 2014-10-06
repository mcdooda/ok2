local cos = math.cos
local sin = math.sin
local pi = math.pi
local pi6 = pi / 6

skill {
	name     = 'specialyellow2',
	cooldown = 0.4,
	trigger  = function(ship)
		popShipMissiles(ship, 'specialyellow1', 4, 0, 40)
		popShipMissiles(ship, 'specialyellow1', 4, 0, 40, pi6)
		local sx, sy = ship:getSpeed()
		local x, y = ship:getPosition()
		local d = 2 / 3
		ship:setPosition(x + sx * d, y + sy * d)
	end
}
