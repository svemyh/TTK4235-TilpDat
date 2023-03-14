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
  BUTTONSTOP = 4,
} elevatorState;

elevatorState state;

void currentState(int currentFloor, elevatorState *state);


