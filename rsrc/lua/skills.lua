local function loadSkill(name)
	dofile('rsrc/lua/skills/' .. name .. '.lua')
	print('skill: ' .. name .. ' [OK]')
end

loadSkill 'blue'
loadSkill 'gray'
loadSkill 'green'
loadSkill 'pink'
loadSkill 'red'
loadSkill 'yellow'

