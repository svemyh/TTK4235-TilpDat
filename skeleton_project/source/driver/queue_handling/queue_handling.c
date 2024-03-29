/**
 * @file
 * @brief The implementation file for queue handling library
 */
#include "queue_handling.h"

int queueMatrix[N_FLOORS][N_BUTTONS] = {
  {0}
};

int checkQueueAbove(int floor) { // check if should be moving up
    if (floor != -1) {
        for (int f = 0; f < N_FLOORS-1; f++) {
            if (queueMatrix[f][2] > 0) {
                return 1; 
            }
        }
    }
    return 0;
}

int checkQueueBelow(int floor) { // check if should be moving down
    if (floor != -1 && floor != 0) {
        for (int f = 0; f < N_FLOORS-1; f--) {
            if (queueMatrix[f][2] > 0) {
                return 1; 
            }
        }
    }
    return 0;
}

void makeRequest() { // as in UP or DOWN buttons. unused
  for (int f = 0; f < N_FLOORS-1; f++) {
    for (int b = 0; b < N_BUTTONS-1; b++) { //yikes
      if (elevio_callButton(f, 0)) { // callButton activated, tells the elevator to stop if dirn_up(not yet implemented)
          queueMatrix[f][0] = 1;
          queueMatrix[f][2] = 1;
      }

      if (elevio_callButton(f, 1)) { // tell the elevator to go down
          queueMatrix[f][1] = 1;
          queueMatrix[f][2] = 1;     // if up or down is requested outside, the elevator will stop when arrived to that floor
      }

      if (elevio_callButton(f, 2)) {
          queueMatrix[f][2] = 1;
      }
    }
  }
}

int checkQueue(void) { //unused
    int sum;
    for (int f = 0; f < N_FLOORS-1; f++) {
        for (int b = 0; b < N_BUTTONS-1; b++) {
            
            sum = sum + queueMatrix[f][b];
            if (sum > 0) {
                return 1;
            }
        }
    }
    return 0;
}
    
void clearQueue(void) {
    elevio_doorOpenLamp(0);
    for(int f = 0; f < N_FLOORS; f++){ //skrur av alle floor lamps
            for(int b = 0; b < N_BUTTONS; b++){
                elevio_buttonLamp(f, b, 0);
            }
        }

    for(int f = 0; f < N_FLOORS-1; f++){
        for (int b = 0; b < N_BUTTONS-1; b++) {
            queueMatrix[f][b] = 0;
        }
    }
}

void clearFloor(int floor) {
    if (floor != -1) {
        for (int b = 0; b < N_BUTTONS-1; b++) {
            queueMatrix[floor][b] = 0;
        }
    }
}


