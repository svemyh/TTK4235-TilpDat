/**
 * @file
 * @brief The implementation file for queue handling library
 */
#include "queue_handling.h"
// for å sjekke error
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <pthread.h>

#include "../elevio.h"
#include "../con_load.h"
#include "../openDoors/openDoors.h"

int checkQueueAbove(int floor) { // check if should be moving up
    if (floor != -1) {
        for (int f = 0; f < N_FLOORS; f++) {
            if (queueMatrix[f][2] > 0) {
                return 1; 
            }
        }
    }
    return 0;
}

int checkQueueBelow(int floor) { // check if should be moving down
    if (floor != -1 && floor != 0) {
        for (int f = 0; f < N_FLOORS; f--) {
            if (queueMatrix[f][2] > 0) {
                return 1; 
            }
        }
    }
    return 0;
}

void makeFloorRequest(int floor) { //unused
    if (elevio_callButton(floor, 2)) {
        queueMatrix[floor][2] = 1;
    }
}

void makeButtonRequest(int floor) { // as in UP or DOWN buttons. unused
    if (elevio_callButton(floor, 0)) { // callButton activated, tells the elevator to stop if dirn_up(not yet implemented)
        queueMatrix[floor][0] = 1;
        queueMatrix[floor][2] = 1;
    }

    if (elevio_callButton(floor, 1)) { // tell the elevator to go down
        queueMatrix[floor][1] = 1;
        queueMatrix[floor][2] = 1;     // if up or down is requested outside, the elevator will stop when arrived to that floor
    }
}

int checkQueue(void) { //unused
    int sum;
    for (int f = 0; f < N_FLOORS; f++) {
        for (int b = 0; b < N_BUTTONS; b++) {
            
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

    for(int i = 0; i < 4; i++){
        for (int j = 0; j < 3; j++) {
            queueMatrix[i][j] = 0;
        }
    }
}

void clearFloor(int floor) {
    if (floor != -1) {
        for (int b = 0; b < N_BUTTONS; b++) {
            queueMatrix[floor][b] = 0;
        }
    }
}


