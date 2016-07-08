#include <Arduino.h>
#include <inttypes.h>
#include <FastLED.h>


#include "utils.h"

#define START_PIN 2
#define LED_DATA_PIN 1

#define NUM_LEDS 81
CRGB leds[NUM_LEDS];

#include "field.h"

#include "controller.h"


char maze[9][10] = {
  "S  *     ",
  "      *  ",
  "*** *****",
  "         ",
  " ***** **",
  "         ",
  "  *******",
  "        E"
};

struct coord9x9 player;
bool gameStarted = false;


void setup(){

  pinMode(START_PIN, INPUT);

  pinMode(UP_ARROW_PIN, INPUT);
  pinMode(DOWN_ARROW_PIN, INPUT);
  pinMode(LEFT_ARROW_PIN, INPUT);
  pinMode(RIGHT_ARROW_PIN, INPUT);


  // subgrid input buttons
  for (uint8_t i = 0; i < 9; i++)
    pinMode(RIGHT_ARROW_PIN + 1 + i, INPUT);



  // populate our led array
  FastLED.addLeds<WS2812B, LED_DATA_PIN, RGB>(leds, 81); // 9 x 9 = 81

}

void loop(){

  if (gameStarted) {

    // change the maze based on input from the user
    field::randSubgrid(controls::subgridInput());

    // turn on the lights
    field::showField();

  /// Checks if there is a cup on the coaster
  /// if so, begin the game and generate the random seed
  } else if (digitalRead(START_PIN)) { 
  
    // use the time taken to start the game as a seed
    randomSeed(micros());
  
    gameStarted = true;
    player = field::findStart();

  } else {

    // field::attractPlayers(); // draw text on the leds
    
  }


}
