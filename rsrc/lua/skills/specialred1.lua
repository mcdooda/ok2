local cos = math.cos
local sin = math.sin
local pi = math.pi

skill {
	name     = 'specialred1',
	cooldown = 5,
	trigger  = function(ship)
		for i = -1, 16 do
			popShipMissiles(ship, 'red', 2, 6, 30, i * pi / 16)
		end
	end
}
