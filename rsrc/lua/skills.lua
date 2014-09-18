local function loadSkill(name)
	dofile('rsrc/lua/skills/' .. name .. '.lua')
	--print('skill: ' .. name .. ' [OK]')
end

loadSkill 'blue1'
loadSkill 'specialblue1'

loadSkill 'gray1'
loadSkill 'specialgray1'

loadSkill 'green1'
loadSkill 'specialgreen1'

loadSkill 'pink1'
loadSkill 'specialpink1'

loadSkill 'red1'
loadSkill 'specialred1'

loadSkill 'yellow1'
loadSkill 'specialyellow1'

