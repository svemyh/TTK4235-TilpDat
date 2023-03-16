/**
 * @file
 * @brief The elevatorState library
 */
#pragma once
#include "../elevio.h"

typedef enum {
  INIT = 0,
  IDLE = 1, 
  MOVING_UP = 2,
  MOVING_DOWN = 3,
  STOP = 4,
} elevatorState;

void currentState(int currentFloor, elevatorState *state);


