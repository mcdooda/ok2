local function loadShip(name)
	dofile('rsrc/lua/ships/' .. name .. '.lua')
	--print('ship: ' .. name .. ' [OK]')
end

loadShip 'blue'

loadShip 'gray'

loadShip 'green'

loadShip 'pink'

loadShip 'red'
loadShip 'red_specialred1'

loadShip 'yellow'

