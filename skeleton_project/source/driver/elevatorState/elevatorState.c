/**
 * @file 
 * @brief The elevatorState implementation file
 */

#include "../elevio.h"
#include "elevatorState.h"
#include "../obstructionAndStop/obstructionAndStop.h"
#include "../openDoors/openDoors.h"
#include "../queue_handling/queue_handling.h"
#include <time.h>

void currentState(int currentFloor, elevatorState *state) {
  switch (*state) {
    case INIT: {
      printf("=======================================\n\n");
      printf("Initializing the elevator\n");

      clearQueue();
      for (int f = 0; f < N_FLOORS; f++) {      //check if queue is cleared
        for (int b = 0; b < N_BUTTONS; b++) {
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
        if (currentFloor != -1) {
          printf("Floor: %d. Please wait \n", currentFloor);
        }
        elevio_motorDirection(DIRN_DOWN);        
      }
      elevio_motorDirection(DIRN_STOP);

      printf("In defined floor: %d \n\n", currentFloor);
      printf("=======================================\n\n");
      *state = IDLE;
      break; 
    }

    case IDLE: {
      obstructionStop();
      if (currentFloor != -1) { // in floor
        elevio_doorOpenLamp(1);
        makeRequest();
        elevio_motorDirection(DIRN_STOP);
        printf("Idle in floor %d \n", currentFloor);

        if (elevio_stopButton()) {
          *state = STOP;
        }
        
        if (checkQueueAbove(currentFloor)) {
          elevio_doorOpenLamp(0);
          elevio_motorDirection(DIRN_UP);
          *state = MOVING_UP;
        }
  
        else if (checkQueueBelow(currentFloor)) {
          elevio_doorOpenLamp(0);
          elevio_motorDirection(DIRN_DOWN);
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
        obstructionStop();
        elevio_doorOpenLamp(0);
        elevio_motorDirection(DIRN_UP);
        makeRequest();

        if (elevio_stopButton()) {
          *state = STOP;
        }

        if (currentFloor == -1) {
          printf("Moving up between floors\n");
          *state = MOVING_UP;
          break;
        }
        //if (currentFloor != -1) 
        if ((queueMatrix[currentFloor][2] == 1 && queueMatrix[currentFloor][1] == 0) && checkQueueAbove(currentFloor) != 0) { // if arrived to requested floor. because we're the type of assholes that wont let passengers in if they request the opposite direction of the elevation direciton, we have them wait till request = direction
          openDoors(currentFloor);
          clearFloor(currentFloor);
          nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
          if (checkQueueAbove(currentFloor)) {            
            *state = MOVING_UP;
            break;
          }
        }

        else if (queueMatrix[currentFloor][1] == 1 && checkQueueAbove(currentFloor == 0)) {
          clearFloor(currentFloor);
          *state = IDLE;
        }

        else if (checkQueueAbove(currentFloor) == 0 && checkQueueBelow(currentFloor) == 0) {
          openDoors(currentFloor);
          clearFloor(currentFloor);
          printf("Entering idle\n");
          *state = IDLE;
        }
    }
    break;

    case MOVING_DOWN: {
        obstructionStop();
        elevio_doorOpenLamp(0);
        elevio_motorDirection(DIRN_DOWN);
        makeRequest();

        if (elevio_stopButton()) {
          *state = STOP;
        }

        if (currentFloor == -1) {
          printf("Moving down between floors\n");
          *state = MOVING_DOWN;
          break;
        }
        //if (currentFloor != -1) 
        if ((queueMatrix[currentFloor][2] == 1 && queueMatrix[currentFloor][0] == 0) && checkQueueBelow(currentFloor) != 0) { // if arrived to requested floor. because we're the type of assholes that wont let passengers in if they request the opposite direction of the elevation direciton, we have them wait till request = direction
          openDoors(currentFloor);
          clearFloor(currentFloor);
          nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
          if (checkQueueAbove(currentFloor)) {            
            *state = MOVING_DOWN;
            break;
          }
        }

        else if (queueMatrix[currentFloor][0] == 1 && checkQueueBelow(currentFloor == 0)) {
          clearFloor(currentFloor);
          *state = IDLE;
        }

        else if (checkQueueAbove(currentFloor) == 0 && checkQueueBelow(currentFloor) == 0) {
          openDoors(currentFloor);
          clearFloor(currentFloor);
          printf("Entering idle\n");
          *state = IDLE;
        }
    }

    break;
    case STOP: {
      stopButton(currentFloor);
      while (elevio_stopButton()) {
        stopButton(currentFloor);
      }

      nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
      elevio_stopLamp(0);
      printf("Restaring system\n");
      *state = INIT;
      break;
    }
  }
}

