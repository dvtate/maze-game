#ifndef MAZE_FIELD_H
#define MAZE_FIELD_H

#include "Arduino.h"
#include <FastLED.h>

#include "utils.h"
#include "controller.h"
#include "maze.h"


extern char maze[9][10];
extern struct coord9x9 player, enemy;
extern bool gameStarted;


namespace field {

  // draws the maze, players, enemy, etc.
  void showField(){
    uint8_t lednum = 0;
    
    // paint the maze
    for (uint8_t r = 0; r < 9; r++)
      for (uint8_t c = 0; c < 9; c++, lednum++)
        switch (maze[r][c]) {
          // the walls are red
          case '#': case 'R':
            leds[lednum] = CRGB::Red;
            break;
          // the path isnt lit up
          case ' ':
            leds[lednum] = CRGB::Black;
            break;
          // the exit/goal/destination is green
          case 'E': case 'G':
            leds[lednum] = CRGB::Green;
            break;
          // the player-spawn is white
          case 'S': case '*': case 'W':
            leds[lednum] = CRGB::White;
            break;
          
          case 'B':
            leds[lednum] = CRGB::Blue;
            break;
        }

    // paint the player blue        
    leds[player.r * 9 + player.c] = CRGB::Blue;

    // paint the enemy orange
    if (enemy.r != 13)
      leds[enemy.r * 9 + enemy.c] = CRGB(255, 165, 0);

    FastLED.show();
  }



  // cordinates of the player-spawn-point
  struct coord9x9 findStart(){

    struct coord9x9 ret;

    for (uint8_t r = 0; r < 9; r++)
      for (uint8_t c = 0; c < 9; c++)
        if (maze[r][c] == 'S') {
          ret.r = r;
          ret.c = c;
          return ret;
        }

    // start not found
    ret.r = 0;
    ret.c = 0;
    return ret;

  }

  // sets the coordinates of the starting and ending points
  static void constantMarkers(const struct coord9x9& coord,
    struct coord9x9* start, struct coord9x9* ending
  ){

    for (int8_t r = -1; r != 2; r++)
      for (int8_t c = -1; c != 2; c++)
        if (maze[coord.r + r][coord.c + c] == 'S') {
          start->r = coord.r + r;
          start->c = coord.c + c;
        } else if (maze[coord.r + r][coord.c + c] == 'E') {
          ending->r = coord.r + r;
          ending->c = coord.c + c;
        }
  
  }

  void randSubgrid(const struct coord9x9 coord){
    ///TODO: this will delete the starting/ending marker!!
    ///       FIX THIS!

    
    if (coord.r != 0) { // if there is a subgrid to randomize

      struct coord9x9 *start = NULL,
                      *ending = NULL;
  
      // find the 'S' & 'E' markers.
      constantMarkers(coord, start, ending);
      

      // use time as a random seed
      randomSeed(micros());

      // union used to convert a random uint16_t 
      // into a random subgrid_t my using a shared
      // space in memory
      union {
        unsigned int randint : 9;  
        struct subgrid_t r;
      };
      


      // this will tamper with r's values making them random 
      randint = random(512);
      
      maze[coord.r - 1][coord.c - 1] = r.m00 ? '#' : ' ';
      maze[coord.r - 1][coord.c] =     r.m01 ? '#' : ' ';
      maze[coord.r - 1][coord.c + 1] = r.m02 ? '#' : ' ';

      maze[coord.r][coord.c - 1] = r.m10 ? '#' : ' ';
      maze[coord.r][coord.c] =     r.m11 ? '#' : ' ';
      maze[coord.r][coord.c + 1] = r.m12 ? '#' : ' ';

      maze[coord.r + 1][coord.c - 1] = r.m20 ? '#' : ' ';
      maze[coord.r + 1][coord.c] =     r.m21 ? '#' : ' ';
      maze[coord.r + 1][coord.c + 1] = r.m22 ? '#' : ' ';

      // redraw the starting and ending locations
      if (start != NULL)
        maze[start->r][start->c] = 'S';
        
      if (ending != NULL)
        maze[ending->r][ending->c] = 'E';
      
    }
  }

  void updatePlayer(){
    
    // get the input from all the buttons
    struct inputDir input = controls::dirInput();

    // if it's safe to move then move...
    
    if (input.up && player.r != 0 && maze[player.r - 1][player.c] != '#')
      player.r--;
      
    if (input.down && player.r != 8 && maze[player.r + 1][player.c] != '#')
      player.r++;
      
    if (input.left && player.c != 0 && maze[player.r][player.c - 1] != '#')
      player.c--;
      
    if (input.right && player.c != 8 && maze[player.r][player.c + 1] != '#')
      player.c++;
      
  }

  // is the  game over
  inline bool gameOver(){
    return (player.r == enemy.r && player.c == enemy.c)   // player touching enemy?
           || maze[player.r][player.c] == 'E';           // is player on the goal?
  }

  // turn all the LED's off
  inline void clearScreen(){
    for (uint8_t i = 0; i < NUM_LEDS; i++)
      leds[i] = CRGB::Black;
  }

  // reset the game board and have some fun :D
  void endGame(){
    
    // clearScreen();

    // display GG 
    Maze::setMaze(Maze::gg);
    showField();
    delay(5000);

    gameStarted = false;
    
    // draw in more players
    Maze::setMaze(Maze::hello);
    showField();

  }

} 

#endif
