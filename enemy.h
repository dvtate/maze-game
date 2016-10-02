#ifndef ENEMY_H
#define ENEMY_H


#include "utils.h"
#include "controller.h"
#include "maze.h"


extern char maze[9][10];
extern struct coord9x9 player;

struct coord9x9 enemy;


namespace Enemy {

  // returns the coordinates of the enemy spawn-point
	static struct coord9x9 findEnemySpawn(){
		struct coord9x9 ret;
    
		for (uint8_t r = 0; r < 9; r++)
			for (uint8_t c = 0; c < 9; c++)
				if (maze[r][c] == 'X') {
					ret.r = r;
					ret.c = c;
					return ret;
				}

		ret.r = 13;
		return ret;
	}


	inline void goToSpawn()
		{ enemy = findEnemySpawn(); }

  // changes the enemy coords if its within the game boundaries
	static void moveEnemy(struct inputDir movement){

	    // if it's safe to move then move...
	    
	    if (movement.up && enemy.r != 0 && maze[enemy.r - 1][enemy.c] != '#')
	      enemy.r--;
	      
	    if (movement.down && enemy.r != 8 && maze[enemy.r + 1][enemy.c] != '#')
	      enemy.r++;
	      
	    if (movement.left && enemy.c != 0 && maze[enemy.r][enemy.c - 1] != '#')
	      enemy.c--;
	      
	    if (movement.left && enemy.c != 8 && maze[enemy.r][enemy.c + 1] != '#')
	      enemy.c++;

     
	}

  // if there's a block in front of the enemy
	static bool blockAhead(struct inputDir movement){
		
		if (movement.up && (enemy.r == 0 || maze[enemy.r - 1][enemy.c] == '#'))
			return true;
		if (movement.down && (enemy.r == 8 || maze[enemy.r + 1][enemy.c] == '#'))
			return true;
		if (movement.left && (enemy.c == 0 || maze[enemy.r][enemy.c - 1] == '#'))
			return true;
		if (movement.right && (enemy.c == 8 || maze[enemy.r][enemy.c + 1] == '#'))
			return true;

		return false;
			
	}

  // returns the direction most opposite to the given direction
	static struct inputDir& reverseDirection(struct inputDir& movement){
		
		if (movement.up) {
			movement.up = false;
			movement.down = true;
		} else if (movement.down) {
			movement.down = false;
			movement.up = true;
		}

		if (movement.left) {
			movement.left = false;
			movement.right = true;
		} else if (movement.right) {
			movement.right = false;
			movement.left = true;
		}

		return movement;
	}

  // determines if the enemy is is trapped
  // and cannot escape
  bool lockedIn(){
    for (int8_t r = -1; r != 2; r++)
      for (int8_t c = -1; c != 2; c++)
        if (maze[enemy.r + r][enemy.c + c] != '#' 
          && enemy.r != 0 && enemy.r != 8
          && enemy.c != 0 && enemy.c != 8
        )
          return false;

    return true;
  }

  // if enemy is only 1 away from player, kill player
  static bool easyKill(struct inputDir& movement){
    // calculate how far away the player is
    struct coord9x9 distToPlayer =
      { player.r - enemy.r, player.c - enemy.c }

    bool easyKill = false; 

    // determine if player is one away
    // move enemy accordingly
    if (distToPlayer.r == 1) { // rows
      enemy.r++;
      easyKill = true;
      movement = {0, 1, 0, 0};
    } else if (distToPlayer.r == -1) {
      enemy.r--;
      easyKill = true;
      movement = {1, 0, 0, 0};
    }

    if (distToPlayer.c == 1) { // cols
      enemy.c++;
      easyKill = true;
      movement.left = false;
      movement.right = true;
    } else if (distToPlayer.c == -1) {
      enemy.c--;
      easyKill = true;
      movement.left = true;
      movement.right = false;
    }

    return easyKill; 
    
    
  }
  
  // this is the 'AI' that governs the enemy's movement
  // this is currently the least functional part of the game
	void updateEnemy(){
    uint16_t crunches = 0; // this is a really sad hack to stop an infinite loop :(
  
		if (enemy.r != 16) {

			static struct inputDir movement = {0, 0, 0, 0};

      if (easyKill(movement))
        return;

      coord9x9 pastLoc = enemy;

			// the movement direction is randomized by corrupting it's memory with
			// a random integer
			union {
				unsigned int val : 4;
				struct inputDir moveDir;
			};


			val = random(16);

      // enemy is most likely to continue to move forward
			if (val < 10) {
continue_or_reverse:
        // if there is no movement direction, calculate a new one
        if (!movement.up && !movement.down && !movement.left && !movement.right)
          goto random_movement;
          
        // move forward or bounce off wall
				if (blockAhead(movement))
					moveEnemy(reverseDirection(movement));
        else 
          moveEnemy(movement);
        
      // try to turn 90 degrees from current direction
			} else if (val < 12) {
        
			  if (movement.up || movement.down)
          if (enemy.c != 0 && maze[enemy.r][enemy.c - 1] != '#') {
            enemy.c--;
            movement = {0, 0, 1, 0};
          } else if (enemy.c != 8 && maze[enemy.r][enemy.c + 1] != '#') {
            enemy.c++;
            movement = {0, 0, 0, 1};
          }
        else if (movement.left || movement.right)
          if (enemy.r != 0 && maze[enemy.r - 1][enemy.c] != '#') {
            enemy.r--;
            movement = {0, 0, 1, 0};
          } else if (enemy.r != 8 && maze[enemy.r + 1][enemy.c] != '#') {
            enemy.r++;
            movement = {0, 0, 0, 1};
          }

        // if there is no movement direction, calculate a new one
        else
          goto random_movement;
			  
			/// this is supposed to randomly generate a new direction
		  } else {
random_movement:        
  //    moveDir = {0, 0, 0, 0};
  //    if (!lockedIn())
  //      while (val == 0 || blockAhead(moveDir))  
				val = random(16); // try replacing this with random(17)...
        crunches++; // (;.;)
				moveEnemy(movement = moveDir);
       
			}
      
      // if there was no movement, try and generate another direction
      if (enemy.r == pastLoc.r && enemy.c == pastLoc.c && !lockedIn() && crunches < 2000)
        goto random_movement;
		}
		
  }

}


#endif
