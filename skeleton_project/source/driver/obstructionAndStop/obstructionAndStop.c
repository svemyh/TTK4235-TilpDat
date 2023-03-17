/**
 * @file 
 * @brief The implementation file of obstructionStop library
 */

#include "obstructionAndStop.h"
#include "../openDoors/openDoors.h"
#include "../elevio.h"

void obstructionStop(void) {
            while(elevio_obstruction()){
                elevio_stopLamp(1);
                printf("OBSTRUCTION DETECTED!\n");
            }
            elevio_stopLamp(0);
            nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
        }

void stopButton(int currentFloor) {
         
                elevio_motorDirection(DIRN_STOP);
                elevio_stopLamp(1);
                if(currentFloor != -1){
                        elevio_doorOpenLamp(1);
                }
                else {
                        elevio_doorOpenLamp(0);
                }
        while (elevio_stopButton()) {
                printf("STOP BUTTON HELD!\n");
        }
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
}


