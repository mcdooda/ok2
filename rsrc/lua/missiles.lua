local function loadMissile(name)
	dofile('rsrc/lua/missiles/' .. name .. '.lua')
	print('missile: ' .. name .. ' [OK]')
end

loadMissile 'blue'
loadMissile 'gray'
loadMissile 'green'
loadMissile 'pink'
loadMissile 'red'
loadMissile 'yellow'

