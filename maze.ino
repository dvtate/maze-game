#include <Arduino.h>
#include <inttypes.h>
#include <FastLED.h>


#include "utils.h"

#define START_PIN 2
#define LED_DATA_PIN 1

#define NUM_LEDS 81
CRGB leds[NUM_LEDS];


#include "controller.h"
#include "maze.h"
#include "field.h"



char maze[9][10];
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



  // populate our screen
  FastLED.addLeds <WS2812B, LED_DATA_PIN, RGB>(leds, NUM_LEDS);


  // say hi on startup :) 
  Maze::setMaze(Maze::hello);
  field::showField();
  delay(2000);

}

void loop(){

  if (gameStarted) {

    // change the maze based on input from the user
    field::randSubgrid(controls::subgridInput());

    // turn on the lights
    field::showField();

    // reset the game once it's over
    if (field::gameOver())
      field::endGame();



      
  /// Checks if there is a cup on the coaster
  /// if so, begin the game and generate the random seed
  } else if (digitalRead(START_PIN)) { 

    // select a random maze
    Maze::pickMaze();

    // put the player at the starting location
    player = field::findStart();

    // start the game
    gameStarted = true;
    
  } else {

    // field::attractPlayers(); // draw text on the leds
    
  }

  delay(500);
}
