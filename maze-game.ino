#include <Arduino.h>
#include <inttypes.h>
#include <FastLED.h>


#include "utils.h"

#define START_PIN 8
#define LED_DATA_PIN A2

#define NUM_LEDS 81 // 9 x 9 = 81
CRGB leds[NUM_LEDS];


#include "controller.h"
#include "maze.h"
#include "field.h"
#include "enemy.h"


char maze[9][10];

struct coord9x9 player;
bool gameStarted = false;


void setup(){

  pinMode(START_PIN, INPUT);

  pinMode(UP_ARROW_PIN, INPUT);
  pinMode(DOWN_ARROW_PIN, INPUT);
  pinMode(LEFT_ARROW_PIN, INPUT);
  pinMode(RIGHT_ARROW_PIN, INPUT);

/*
  // subgrid input buttons
  for (uint8_t i = 0; i < 9; i++)
    pinMode(RIGHT_ARROW_PIN + 1 + i, INPUT);
*/
  
  pinMode(GRID_PIN_00, INPUT);
  pinMode(GRID_PIN_01, INPUT);
  pinMode(GRID_PIN_02, INPUT);
  pinMode(GRID_PIN_10, INPUT);
  pinMode(GRID_PIN_11, INPUT);
  pinMode(GRID_PIN_12, INPUT);
  pinMode(GRID_PIN_20, INPUT);
  pinMode(GRID_PIN_21, INPUT);
  pinMode(GRID_PIN_22, INPUT);

  // link the colors to the LEDs
  FastLED.addLeds <WS2812B, LED_DATA_PIN, GRB>(leds, NUM_LEDS);

  // say hi on startup :P
  Maze::setMaze(Maze::hello);
  field::showField();
  delay(2000);

}

void loop(){

  if (gameStarted) {

    // change the maze based on input from the user
    field::randSubgrid(controls::subgridInput());

    // update the player and enemy positions
    field::updatePlayer();
    Enemy::updateEnemy();

    // turn on the lights
    field::showField();


    // enemy kills you or you reach the destination
    if (field::gameOver())
      field::endGame(); // reset the game once it's over


    
    
  /// Checks if there is a cup on the coaster?
  /// if so, begin the game and generate the random seed
  } else if (digitalRead(START_PIN)) { 

    // select a random maze
    Maze::pickMaze();

    // put the player at the starting location
    player = field::findStart();

    // start the game
    gameStarted = true;

    Enemy::goToSpawn();

  }

  delay(250);
}
