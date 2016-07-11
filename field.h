#ifndef MAZE_FIELD_H
#define MAZE_FIELD_H

#include "Arduino.h"
#include <FastLED.h>


#include "utils.h"

#include "controller.h"
#include "maze.h"

extern char maze[9][10];
extern struct coord9x9 player;



struct subgrid_t {
  bool m00 : 1, m01 : 1, m02 : 1,
       m10 : 1, m11 : 1, m12 : 1,
       m20 : 1, m21 : 1, m22 : 1;
};




namespace field {


  CRGB leds[81];
  
  void showField(){
    for (uint8_t x = 0; x < 9; x++)
      for (uint8_t y = 0; y < 9; y++)
        if (maze[x][y] == '#')
          leds[(x * 9) + y] = CRGB::Red;
        else if (maze[x][y] == ' ')
          leds[(x * 9) + y] = CRGB::Black;
        else if (maze[x][y] == 'E')
          leds[(x * 9) + y] = CRGB::Green;
        else 
          leds[(x * 9) + y] = CRGB::Blue;

    leds[player.x * 9 + player.y] = CRGB::Blue;


    FastLED.show();
  }




  struct coord9x9 findStart(){

    struct coord9x9 ret;

    for (uint8_t x = 0; x < 9; x++)
      for (uint8_t y = 0; y < 9; y++)
        if (maze[x][y] == 'S') {
          ret.x = x;
          ret.y = y;
          return ret;
        }

    // start not found
    ret.x = 0;
    ret.y = 0;
    return ret;

  }

  void randSubgrid(struct coord9x9 coord){
    if (coord.x != 0) {

      // use time as a random seed
      randomSeed(micros());

      // union used to convert a random uint16_t 
      // into a random subgrid_t my using a shared
      // space in memory
      union {
        uint16_t randint;  
        struct subgrid_t r;
      };


      // this will tamper with r's values making them random 
      randint = random(65535);
      
      maze[coord.x - 1][coord.y - 1] = r.m00 ? '#' : ' ';
      maze[coord.x - 1][coord.y] =     r.m01 ? '#' : ' ';
      maze[coord.x - 1][coord.y + 1] = r.m02 ? '#' : ' ';

      maze[coord.x][coord.y - 1] = r.m10 ? '#' : ' ';
      maze[coord.x][coord.y] =     r.m11 ? '#' : ' ';
      maze[coord.x][coord.y + 1] = r.m12 ? '#' : ' ';

      maze[coord.x + 1][coord.y - 1] = r.m20 ? '#' : ' ';
      maze[coord.x + 1][coord.y] =     r.m21 ? '#' : ' ';
      maze[coord.x + 1][coord.y + 1] = r.m22 ? '#' : ' ';
    }
  }



  void updatePlayer(){
    
    // get the input from all the buttons
    struct inputDir input = controls::dirInput();

    // if it's safe to move then move
    if (input.up && player.x != 0 && maze[player.x - 1][player.y] != '#')
      player.x--;
    if (input.down && player.x != 8 && maze[player.x + 1][player.y] != '#')
      player.x++;
    if (input.left && player.y != 0 && maze[player.x][player.y - 1] != '#')
      player.y--;
    if (input.left && player.y != 8 && maze[player.x][player.y + 1] != '#')
      player.y++;
      
  }


  inline bool gameOver()
    { return maze[player.x][player.y] == 'E'; }

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

    // draw in more players
    Maze::setMaze(Maze::hello);
    showField();
    
  }

} 


#endif
