/**
 * @file 
 * @brief elevatorState implementation file
 */
#include "elevatorState.h"
#include "../obstructionAndStop/obstructionAndStop.h"
#include "../openDoors/openDoors.h"
#include "../queue_handling/queue_handling.h"

extern MotorDirection currentDirection;
extern int queueMatrix[N_FLOORS][N_BUTTONS];

void currentState(int currentFloor, elevatorState *state) {
  switch (*state) {
    case INIT:
      printf("Initializing the elevator\n");
      clearQueue();
      while (currentFloor > 1) { //defines defined floor = 1
        elevio_motorDirection(DIRN_DOWN);
      }

      while (currentFloor < 1) {
        elevio_motorDirection(DIRN_UP);
      }
      *state = IDLE;
      break; 

    case IDLE:
      currentDirection = DIRN_STOP;
      elevio_doorOpenLamp(1);
      if (elevio_stopButton()) {
        *state = BUTTONSTOP;
      }

      if (checkQueueAbove(currentFloor)) {
        *state = MOVING_UP;
      }

      else if (checkQueueBelow(currentFloor)) {
        *state = MOVING_DOWN;
      }
      break;

    case MOVING_UP:
    elevio_motorDirection(DIRN_UP);

      if (elevio_stopButton()) {
        *state = BUTTONSTOP;
      }

      else if ((queueMatrix[currentFloor][2] == 1 && queueMatrix[currentFloor][1] != 0) || currentFloor == 4) { // if arrived to requested floor. because we're the type of assholes that wont let passengers in if they request the opposite direction of the elevation direciton, we have them wait till request = direction
        openDoors(currentFloor);
        clearFloor(currentFloor);
        if (checkQueueAbove(currentFloor)) {
          *state = MOVING_UP;
        }

        else {
          *state = IDLE;
        }
      }
      else {
        *state = MOVING_UP;
      }
      break;

    case MOVING_DOWN:
      elevio_motorDirection(DIRN_DOWN);

      if (elevio_stopButton()) {
        *state = BUTTONSTOP;
      }

      else if ((queueMatrix[currentFloor][2] == 1 && queueMatrix[currentFloor][0] != 0) || currentFloor == 4) { // if arrived to requested floor
        openDoors(currentFloor);
        clearFloor(currentFloor);
        if (checkQueueAbove(currentFloor)) {
          *state = MOVING_DOWN;
        }

        else {
          *state = IDLE;
        }
      }
      else {
        *state = MOVING_DOWN;
      }
      break;

    case BUTTONSTOP:
      stopButton(currentFloor);
      *state = INIT;
      break;

    default:
      printf("INVALID\n");
      *state = INIT;
      break;
  }
}
