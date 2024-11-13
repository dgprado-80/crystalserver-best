local increasing = { [419] = 420, [431] = 430, [452] = 453, [563] = 564, [549] = 562, [10145] = 10146 }
local decreasing = { [420] = 419, [430] = 431, [453] = 452, [564] = 563, [562] = 549, [10146] = 10145 }

local tile = MoveEvent()

function tile.onStepIn(creature, item, position, fromPosition)
	local player = creature:getPlayer()
	if not player or player:isInGhostMode() then
		return true
	end

	if not increasing[item.itemid] then
		return true
	end

	item:transform(increasing[item.itemid])

	if item.actionid >= 1000 then
		if player:getLevel() < item.actionid - 1000 then
			player:teleportTo(fromPosition, false)
			position:sendMagicEffect(CONST_ME_MAGIC_BLUE)
			player:sendTextMessage(MESSAGE_LOOK, "The tile seems to be protected against unwanted intruders.")
		end
		return true
	end

	if Tile(position):hasFlag(TILESTATE_PROTECTIONZONE) then
		for _, direction in ipairs(DIRECTIONS_TABLE) do
			local playerPosition = player:getPosition()
			playerPosition:getNextPosition(direction)

			local depotItem = playerPosition:getTile():getItemByType(ITEM_TYPE_DEPOT)
			if depotItem then
				local depotItems = 0

				for id = 1, configManager.getNumber(configKeys.DEPOT_BOXES) do
					depotItems = depotItems + player:getDepotChest(id, true):getItemHoldingCount()
				end

				local depotMessage = "Your depot contains " .. depotItems .. " item" .. (depotItems ~= 1 and "s." or ".")
				local stashMessage = "Your supply stash contains " .. player:getStashCount() .. " item" .. (player:getStashCount() ~= 1 and "s." or ".")

				player:sendTextMessage(MESSAGE_FAILURE, depotMessage .. "\n" .. stashMessage)
				player:setSpecialContainersAvailable(true, true, true)
				return true
			end
		end
	end

	if item.actionid ~= 0 and player:getStorageValue(item.actionid) <= 0 then
		player:teleportTo(fromPosition, false)
		position:sendMagicEffect(CONST_ME_MAGIC_BLUE)
		player:sendTextMessage(MESSAGE_EVENT_ADVANCE, "The tile seems to be protected against unwanted intruders.")
		return true
	end
	return true
end

for index, value in pairs(increasing) do
	tile:id(index)
end

tile:type("stepin")
tile:register()

tile = MoveEvent()

function tile.onStepOut(creature, item, position, fromPosition)
	local player = creature:getPlayer()
	if not player or player:isInGhostMode() then
		return true
	end

	if not decreasing[item.itemid] then
		return true
	end

	item:transform(decreasing[item.itemid])
	player:setSpecialContainersAvailable(false, false, false)
	return true
end

for index, value in pairs(decreasing) do
	tile:id(index)
end

tile:type("stepout")
tile:register()
