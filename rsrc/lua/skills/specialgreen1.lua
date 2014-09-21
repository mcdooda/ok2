local cos = math.cos
local sin = math.sin
local pi = math.pi
local pi32 = pi / 32

skill {
	name     = 'specialgreen1',
	cooldown = 2,
	trigger  = function(ship)
		for i = 0, 2 do
			timer(i * 0.1, nil, function()
				popShipMissiles(ship, 'green', 10, 0, 40, pi32 * i)
			end)
		end
	end
}
