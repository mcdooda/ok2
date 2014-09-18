local function loadTemplates(templateType)
	dofile('rsrc/lua/' .. templateType .. '.lua')
	--print('* ' .. templateType .. ' LOADED')
end

loadTemplates 'skills'
loadTemplates 'ships'
loadTemplates 'missiles'
