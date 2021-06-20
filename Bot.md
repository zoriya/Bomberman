# Bot documentation

A bot in this bomberman is using a lua script as way to choose what to do
So you can make your own with some helper functions given from C++

## Update function

Each frame, the game will call the "Update" function in the script.
This is the same lua state as the last call so this means you can set global variables to keep data between frames

Update function should take no arguments.

## Map Blocks

```lua
nothing = 0
breakable = 1
hole = 2
bumper = 4
unbreakable = 7
bomb = 10
```

## Registered functions

```lua
-- getMap returns a table of the blocks of the map
-- From 1 to 17 {{0, 1, 2 ..}, ..}
function getMap();

-- getDanger returns a table of the danger zone on the map
-- From 1 to 17 {{0, 1, 2 ..}, ..}
-- value is number of seconds before explosion
function getDanger();

-- getPath returns a table of nodes of a path from A to B {{x = X, y = Y}, ...}
-- @param x1 should be int
-- @param y1 should be int
-- @param x2 should be int
-- @param y2 should be int
-- @param throughBreakable bool path is going through breakables blocks or not
function getPath(x1, y1, x2, y2, throughBreakable);

-- getPlayer returns player pos as {x = xPlayer, y = yPlayer}
function getPlayer();

-- getPlayerRound  returns player pos with rounded value {x = xPlayer, y = yPlayer}
function getPlayerRound();

-- getDangerLevel returns danger level at [xpos, ypos]
function getDangerLevel(xpos, ypos);

-- getDangerLevelPlayer get danger level on the position of the player
function getDangerLevelPlayer();

-- getBlockType returns block type at [xpos, ypos]
function getBlockType(xpos, ypos);

-- getClosestSafeSpace returns the block next to player where the player should go to to the closest safe space
-- returns player pos if no path is found
function getClosestSafeSpace();

-- canPutBombSafe returns true if player can put a bomb and find a path to safe space if bomb is put
function canPutBombSafe();

-- getRadius returns the explosion radius of the current player
function getRadius();

-- getEnemies returns a table with enemies position {{x = X, y = Y}, ...}
function getEnemies();

-- getEnemies returns a table with enemies position rounded {{x = X, y = Y}, ...}
function getEnemiesRound();
```