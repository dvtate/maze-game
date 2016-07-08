#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <Arduino.h>

#include "utils.h"


/// change these values :)
#define UP_ARROW_PIN 3
#define RIGHT_ARROW_PIN 4
#define DOWN_ARROW_PIN 5
#define LEFT_ARROW_PIN 6

#define GRID_PIN_00 7
#define GRID_PIN_01 8
#define GRID_PIN_02 9
#define GRID_PIN_10 10
#define GRID_PIN_11 11
#define GRID_PIN_12 12
#define GRID_PIN_20 13
#define GRID_PIN_21 14
#define GRID_PIN_22 15


struct inputDir {
  bool up : 1,
     down : 1,
     left : 1,
     right : 1;
};


namespace controls {

  struct inputDir dirInput(){
    struct inputDir ret;
    ret.up = digitalRead(UP_ARROW_PIN);
    ret.down = digitalRead(DOWN_ARROW_PIN);
    ret.left = digitalRead(LEFT_ARROW_PIN);
    ret.right = digitalRead(RIGHT_ARROW_PIN);
    return ret;
  }

  struct coord9x9 subgridInput(){
    
    struct coord9x9 ret;

    if (digitalRead(GRID_PIN_00)) {
      ret.x = 1;
      ret.y = 1;
    } else if (digitalRead(GRID_PIN_01)) {
      ret.x = 1;
      ret.y = 4;
    } else if (digitalRead(GRID_PIN_02)) {
      ret.x = 1;
      ret.y = 7;
    } else if (digitalRead(GRID_PIN_10)) {
      ret.x = 4;
      ret.y = 1;
    } else if (digitalRead(GRID_PIN_11)) {
      ret.x = 4;
      ret.y = 4;
    } else if (digitalRead(GRID_PIN_12)) {
      ret.x = 4;
      ret.y = 7;
    } else if (digitalRead(GRID_PIN_20)) {
      ret.x = 7;
      ret.y = 1;
    } else if (digitalRead(GRID_PIN_21)) {
      ret.x = 7;
      ret.y = 4;
    } else if (digitalRead(GRID_PIN_22)) {
      ret.x = 7;
      ret.y = 7;
    } else 
      ret.x = ret.y = 0;

    return ret;
  }



}

#endif
