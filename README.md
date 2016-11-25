# maze-game
- An arduino controlled coffee-table LED maze game.
- I made this with a team of fellow engineering majors at GHP (governors honors program) in 2016.
- This code was designed to run on an arduino nano
# How the game works
- There are 9 3x3 tiles arranged in a grid. 
- The game is started by pressing the starting tile (top left)
- A random maze will be selected, and the walls will be painted red
- The player (a certain color LED) is controlled by 4 buttons representing the 4 cardinal directions.
- The walls can be randomized by pressing the tile, randomizing the leds (and the maze pattern) on that tile.
- There is an enemy which has semi-random movement, if the player gets too close to the enemy, the player is killed.
- The goal is for the player to make it to the end of the maze.
- If the player is killed or reaches the end of the maze, the board says "GG" and the game is over. 
- Once the board says "Hi!" again, the game can be restarted and a random maze will be selected like last time.

