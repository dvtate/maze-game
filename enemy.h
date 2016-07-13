#ifndef ENEMY_H
#define ENEMY_H

#include "utils.h"

struct coord9x9 enemy;

namespace Enemy {

	static inline struct coord9x9 findEnemySpawn(){
		
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

	static bool blockAhead(struct inputDir movement){
		
		if (movement.up && maze[enemy.r - 1][enemy.c] != '#')
			return true;
		if (movement.down && maze[enemy.r + 1][enemy.c] != '#')
			return true;
		if (movement.left && maze[enemy.r][enemy.c - 1] != '#')
			return true;
		if (movement.right && maze[enemy.r][enemy.c + 1] != '#')
			return true;

		return false;
			
	}

	static struct inputDir reverseDirection(struct inputDir movement){
		
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

	void updateEnemy(){
		if (enemy.r != 16) {

			static struct inputDir movement = {0, 0, 0, 0};

			int8_t rDist = player.r - enemy.r, 
				     cDist = player.c - enemy.c;


			bool easyKill = false; 

			if (rDist == 1) {
				enemy.r++;
				easyKill = true;
				movement = {0, 1, 0, 0};
			} else if (rDist == -1) {
				enemy.r--;
				easyKill = true;
				movement = {1, 0, 0, 0};
			}

			if (cDist == 1) {
				enemy.c++;
				easyKill = true;
				movement.left = false;
				movement.right = true;
			} else if (cDist == -1) {
				enemy.c--;
				easyKill = true;
				movement.left = true;
				movement.right = false;
			}

			if (easyKill) 
				return;

			// the movement direction is randomized by corrupting it's value with
			// a random integer
			union {
				unsigned int val : 4;
				struct inputDir moveDir;
			};


			val = random(16);

      /// enemy is most likely to move forward, 
			if (val < 10) {
continue_or_reverse:
				moveEnemy(movement);
				if (blockAhead(movement))
					moveEnemy(reverseDirection(movement));

			} else if (val < 12) {
			  if (movement.up || movement.down)
          if (enemy.c != 0 && maze[enemy.r][enemy.c - 1] != '#') {
            enemy.c--;
            enemy.movement = {0, 0, 1, 0};
          } else if (enemy.c != 0 && maze[enemy.r][enemy.c + 1] != '#') {
            enemy.c++;
            enemy.movement = {0, 0, 0, 1};
          }
        else if (movement.left || movement.right)
          if (enemy.r != 0 && maze[enemy.r - 1][enemy.c] != '#') {
            enemy.r--;
            enemy.movement = {0, 0, 1, 0};
          } else if (enemy.r != 0 && maze[enemy.r + 1][enemy.c] != '#') {
            enemy.r++;
            enemy.movement = {0, 0, 0, 1};
          }

        else
          goto continue_or_reverse;
			  
			  
		  } else {
				while (blockAhead(moveDir))
					val = random(16);
				moveEnemy(move);
				movement = move;
			}
		}
		
  }


}





#endif
