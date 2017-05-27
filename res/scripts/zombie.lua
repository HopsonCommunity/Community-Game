trackDistance = 7
target = false

function distance(x0, y0, x1, y1)
	dx = x0 - x1
	dy = y0 - y1

	return math.sqrt(dx * dx + dy * dy)
end

function update(entity, app)

	if entity:isMoving() then       -- If the player is moving
		entity:setAnimation("run")  -- set animation to run
	else
		entity:setAnimation("idle") -- otherwise set to idle
	end

	if target then
		-- Update the path to the player
		pathFind = entity:getPathFind()
		pathFind:updatePath(entity:getX(), entity:getY(), entity:getPlayer():getX(), entity:getPlayer():getY())

		if pathFind:getPathSize() > trackDistance * 1.5 then
			target = false
		end

		-- Get the next step of the path
		nextX = pathFind:getNextX()
		nextY = pathFind:getNextY()

		-- Declare variables that
		-- will control zombie movement
		xa = 0
		ya = 0

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
	else
		if (distance(entity:getPlayer():getX(), entity:getPlayer():getY(), entity:getX(), entity:getY()) <= trackDistance * 32) then
			target = true;
		else
			entity:setMoving(false)
		end
	end
end