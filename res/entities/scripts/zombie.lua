-- Some vars that get used in the AI
local track_distance = 16
local target = false

-- Holding a LuaPathFind helper
local pathFind = nil

-- Used in calculating the path, making sure it's
-- only updated ~0.6 times a second
local g_Timer = 0

function update(entity, app)
	-- x, y vars to hold entity position
	-- during this update cycle
	local x = entity:getX()
	local y = entity:getY()

	-- Init pathfind only once instead of every frame
	if pathFind == nil then
		pathFind = entity:getPathFind()
	end

	if entity:isMoving() then       -- If the zombie is moving
		entity:setAnimation("run")  -- set animation to run
	else
		entity:setAnimation("idle") -- otherwise set to idle
	end

	if target then
		-- Update the path to the player
		if g_Timer == 0 then 
			pathFind:updatePath(x, y, entity:getPlayer():getX(), entity:getPlayer():getY())
		end
		
		-- Maintain the timer
		g_Timer = g_Timer + 1
		if g_Timer > 1 then
			g_Timer = 0
		end

		if pathFind:getPathSize() > track_distance * 1.5 then
			g_Timer = 0
			target = false
		end

		-- Get the next step of the path
		local nextX = pathFind:getNextX()
		local nextY = pathFind:getNextY()

		-- Declare variables that
		-- will control zombie movement
		local xa = 0
		local ya = 0

		-- Increment xa, ya depending on path
		if (entity:getX() < nextX) then
			xa = xa + 1
		end
		if (entity:getX() > nextX) then
			xa = xa - 1
		end
		if (entity:getY() < nextY) then
			ya = ya + 1
		end
		if (entity:getY() > nextY) then
			ya = ya - 1
		end

		-- If atleast one of the vars (xa or ya) is not 0
		-- then move the zombie
		if xa ~= 0 or ya ~= 0 then
			entity:setVelocity(xa, ya) -- setVelocity changes 'moving' to true (this controls animation)
		else
			entity:setMoving(false) -- Otherwise set zombie 'moving' to false (this controls animation)
		end

		if xa > 0 then
			entity:setSpriteFlip(false) 
		end
		if xa < 0 then
			entity:setSpriteFlip(true) 
		end
	else
		--@TODO: Tile flood instead of this
		if distance(entity:getPlayer():getX(), entity:getPlayer():getY(), x, y) <= track_distance * Const.TileSize then
			target = true
		else
			entity:setMoving(false)
		end
	end
end

-- Function used to determine distance between 2 points
-- in this script it is used to calculate distance between zombie and player
function distance(x1, y1, x2, y2)
	dx = x1 - x2
	dy = y1 - y2

	return math.sqrt(dx * dx + dy * dy)
end