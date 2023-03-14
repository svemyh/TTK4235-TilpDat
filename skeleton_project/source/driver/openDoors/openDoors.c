/**
 * @file
 * @brief Implementation file of openDoors library
 */
#include "openDoors.h"

#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include "../elevio.h"
#include "../con_load.h"
#include "../obstructionAndStop/obstructionAndStop.h"


void openDoors(int currentFloor) {
    elevio_doorOpenLamp(1); 
    printf("Door has opened at floor %d\n", elevio_floorSensor());
    if (elevio_obstruction()) {
        obstructionStop(); 
    }
    if (elevio_stopButton()) {
        stopButton(currentFloor);
    }

    sleep(3); //venter 3 sekunder
    elevio_doorOpenLamp(0); //skrur lampa av

}

