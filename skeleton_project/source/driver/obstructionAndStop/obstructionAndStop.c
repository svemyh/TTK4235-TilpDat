/**
 * @file 
 * @brief The implementation file of obstructionStop library
 */

#include "obstructionAndStop.h"
#include "../openDoors/openDoors.h"
#include "../elevio.h"

void obstructionStop(void) {
            if(elevio_obstruction()){
                elevio_stopLamp(1);
                printf("OBSTRUCTION DETECTED!\n");
            }

            else {
                elevio_stopLamp(0);
            }
        }

void stopButton(int currentFloor) {
        if(elevio_stopButton()){
                elevio_motorDirection(DIRN_STOP);
                elevio_stopLamp(1);
                if(currentFloor != -1){
                        elevio_doorOpenLamp(1);
                }
                while(elevio_stopButton()) {
                        printf("STOP BUTTON HELD!\n");
                };
                elevio_stopLamp(0);
                sleep(3);
        }
}


