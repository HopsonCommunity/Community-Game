
-- This method gets called from the code constantly. Each entity script should start here
function update(entity, app)

	if entity:isMoving() then       -- If the player is moving
		entity:setAnimation("run")  -- set animation to run
	else
		entity:setAnimation("idle") -- otherwise set to idle
	end

	-- Declare variables that
	-- will control player movement
	xa = 0
	ya = 0

	-- Increment xa, ya depending on keyboard input
	if app:keyPressed("MOVE_UP") then
		ya = ya - 1
	end
	if app:keyPressed("MOVE_DOWN") then
		ya = ya + 1
	end
	if app:keyPressed("MOVE_LEFT") then
		xa = xa - 1
	end
	if app:keyPressed("MOVE_RIGHT") then
		xa = xa + 1
	end

	-- If atleast one of the vars (xa or ya) is not 0
	-- then move the player
	if xa ~= 0 or ya ~= 0 then
		entity:setVelocity(xa, ya) -- setVelocity changes 'moving' to true (this controls animation)
	else
		entity:setMoving(false) -- Otherwise set player 'moving' to false (this controls animation)
	end

	-- Check if mousePos.x < screen width
	-- This makes player 'look' at mouse
	if app:mouseX() < app:screenWidth() / 2 then
		entity:setSpriteFlip(true) 
	else
		entity:setSpriteFlip(false)
	end

	-- Face the player the direction he is moving
	if xa > 0 then
		entity:setSpriteFlip(false) 
	end
	if xa < 0 then
		entity:setSpriteFlip(true) 
	end
end