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

  void showField(){
    uint8_t lednum = 0;
    for (uint8_t r = 0; r < 9; r++)
      for (uint8_t c = 0; c < 9; c++)
        if (maze[r][c] == '#')
          leds[lednum++] = CRGB::Red;
        else if (maze[r][c] == ' ')
          leds[lednum++] = CRGB::Black;
        else if (maze[r][c] == 'E')
          leds[lednum++] = CRGB::Green;
        else 
          leds[lednum++] = CRGB::Blue;

    leds[player.r * 9 + player.c] = CRGB::Blue;


    FastLED.show();
  }




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


  static void constantMarkers(const struct coord9x9 coord,
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

    
    if (coord.r != 0) {

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
        uint16_t randint;  
        struct subgrid_t r;
      };


      // this will tamper with r's values making them random 
      randint = random(65535);
      
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

    // if it's safe to move then move
    if (input.up && player.r != 0 && maze[player.r - 1][player.c] != '#')
      player.r--;
    if (input.down && player.r != 8 && maze[player.r + 1][player.c] != '#')
      player.r++;
    if (input.left && player.c != 0 && maze[player.r][player.c - 1] != '#')
      player.c--;
    if (input.left && player.c != 8 && maze[player.r][player.c + 1] != '#')
      player.c++;
      
  }


  inline bool gameOver()
    { return maze[player.r][player.c] == 'E'; }

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
