/**
 * @file 
 * @brief The elevatorState implementation file
 */

#include "../elevio.h"
#include "elevatorState.h"
#include "../obstructionAndStop/obstructionAndStop.h"
#include "../openDoors/openDoors.h"
#include "../queue_handling/queue_handling.h"

void currentState(int currentFloor, elevatorState *state) {
  switch (*state) {
    case INIT: {
      printf("=======================================\n\n");
      printf("Initializing the elevator\n");

      clearQueue();
      for (int f = 0; f < N_FLOORS-1; f++) {      //check if queue is cleared
        for (int b = 0; b < N_BUTTONS-1; b++) {
          queueMatrix[f][b] = 0;
          elevio_buttonLamp(f, b, 0);
          int queueSum = 0;
          queueSum += queueMatrix[f][b];
          if (queueSum != 0) { //failsafe
            printf("Queue not empty. Trying to initialize again\n");
            *state = INIT;
            break;
          }
        }
      }

      printf(" * Queue cleared\n");
      
      elevio_doorOpenLamp(0);
      printf(" * Doors closed\n");

      elevio_stopLamp(0);
      printf(" * Stop lamps off\n");

      printf("* Button lamps off\n");

      while (currentFloor != 0) { //defines init floor = 0
        currentFloor = elevio_floorSensor();
        printf("Floor: %d. Please wait \n", currentFloor);
        elevio_motorDirection(DIRN_DOWN);        
      }
      elevio_motorDirection(DIRN_STOP);

      printf("In defined floor: %d \n\n", currentFloor);
      printf("=======================================\n\n");
      *state = IDLE;
      break; 
    }

    case IDLE: {
      if (currentFloor != -1) {
        while (elevio_obstruction()) {
          obstructionStop();
        }
        elevio_doorOpenLamp(1);
        elevio_motorDirection(DIRN_STOP);
        printf("Idle in floor %d \n", currentFloor);
        if (elevio_stopButton() || elevio_obstruction()) {
          *state = STOP;
        }
        
        if (checkQueueAbove(currentFloor)) {
          elevio_doorOpenLamp(0);
          *state = MOVING_UP;
        }
  
        else if (checkQueueBelow(currentFloor)) {
          elevio_doorOpenLamp(0);
          *state = MOVING_DOWN;
        }
      }
      else {
        printf("ERROR in IDLE. Restarting\n");
        *state = INIT;
      }
      break;
    }

    case MOVING_UP: {
        elevio_motorDirection(DIRN_UP);
        printf("Moving up. Currently in floor %d \n", currentFloor);
        if (elevio_stopButton()) {
            *state = STOP;
            break;
        }
        //if (currentFloor != -1) 
        if ((queueMatrix[currentFloor][2] == 1 && queueMatrix[currentFloor][1] == 1) || currentFloor == 3) { // if arrived to requested floor. because we're the type of assholes that wont let passengers in if they request the opposite direction of the elevation direciton, we have them wait till request = direction
          openDoors(currentFloor);
          clearFloor(currentFloor);
          if (checkQueueAbove(currentFloor)) {            
            *state = MOVING_UP;
          }
        }
        else if (currentFloor == -1) {
          *state = MOVING_UP;
        }
        else {
        printf("ERROR in MOVING_UP. Restarting\n");
        }
      *state = INIT;
    }
    break;

    case MOVING_DOWN: {
      elevio_motorDirection(DIRN_DOWN);
      printf("Moving down. Currently in floor %d \n", currentFloor);
      if (elevio_stopButton()) {
        *state = STOP;
      }
      
        if ((queueMatrix[currentFloor][2] == 1 && queueMatrix[currentFloor][0] != 0) || currentFloor == 4) { // if arrived to requested floor
          openDoors(currentFloor);
          clearFloor(currentFloor);
          if (checkQueueAbove(currentFloor)) {
            *state = MOVING_DOWN;
          }
        }
      
      else {
        printf("ERROR in MOVING_DOWN. Restarting\n");
        *state = INIT;
      }
      break;
    }

    case STOP: {
      stopButton(currentFloor);
      *state = INIT;
    }

    default: {
      printf("INVALID\n");
      *state = INIT;
      break;
    }
  }
}
