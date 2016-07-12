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

	static void moveEnemy(struct inputDir input){

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


	void updateEnemy(){
		uint8_t val = random(255);

		static struct  inputDir movement = {0,0,0,0};

		int8_t rDist = player.r - enemy.r, 
			     cDist = player.c - enemy.c;

		

		if (rDist == 1)



		} else if (rDist == -1) {


		} 


		if (val > 50) {

		} else if (val )
			



	}

}





#endif
