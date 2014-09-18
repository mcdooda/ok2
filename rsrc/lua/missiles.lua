local function loadMissile(name)
	dofile('rsrc/lua/missiles/' .. name .. '.lua')
	--print('missile: ' .. name .. ' [OK]')
end

loadMissile 'blue1'
loadMissile 'specialblue1'

loadMissile 'gray'
loadMissile 'green'
loadMissile 'pink'
loadMissile 'red'
loadMissile 'yellow'

