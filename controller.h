#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <Arduino.h>

#include "utils.h"



// D-pad button pins
#define DOWN_ARROW_PIN A1
#define UP_ARROW_PIN A2
#define RIGHT_ARROW_PIN A3
#define LEFT_ARROW_PIN A4

// pin numbers for sub-grid input buttons
#define GRID_PIN_00 3
#define GRID_PIN_01 4
#define GRID_PIN_02 2
#define GRID_PIN_10 5 
#define GRID_PIN_11 8
#define GRID_PIN_12 7
#define GRID_PIN_20 6
#define GRID_PIN_21 9
#define GRID_PIN_22 10


// used for storing D-pad input
struct inputDir {
  bool up    : 1,
       down  : 1,
       left  : 1,
       right : 1;
};


namespace controls {
  
  // get D-pad input
  inline struct inputDir dirInput(){
    struct inputDir ret;
    ret.up =    digitalRead(UP_ARROW_PIN);
    ret.down =  digitalRead(DOWN_ARROW_PIN);
    ret.left =  digitalRead(LEFT_ARROW_PIN);
    ret.right = digitalRead(RIGHT_ARROW_PIN);
    return ret;
  }

  // find pressed subgrid, return LED coords
  struct coord9x9 subgridInput(){
    
    struct coord9x9 ret;

    // this means that the top-left 
    // subgrids take priority
    if (digitalRead(GRID_PIN_00)) {
      ret.r = 1;
      ret.c = 1;
    } else if (digitalRead(GRID_PIN_01)) {
      ret.r = 1;
      ret.c = 4;
    } else if (digitalRead(GRID_PIN_02)) {
      ret.r = 1;
      ret.c = 7;
    } else if (digitalRead(GRID_PIN_10)) {
      ret.r = 4;
      ret.c = 1;
    } else if (digitalRead(GRID_PIN_11)) {
      ret.r = 4;
      ret.c = 4;
    } else if (digitalRead(GRID_PIN_12)) {
      ret.r = 4;
      ret.c = 7;
    } else if (digitalRead(GRID_PIN_20)) {
      ret.r = 7;
      ret.c = 1;
    } else if (digitalRead(GRID_PIN_21)) {
      ret.r = 7;
      ret.c = 4;
    } else if (digitalRead(GRID_PIN_22)) {
      ret.r = 7;
      ret.c = 7;
    } else {
      ret.r = 0;
      ret.c = 0;
    }
    
    return ret;
  }

}

#endif // CONTROLLER_H
