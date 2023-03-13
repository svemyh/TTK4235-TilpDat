#include "openDoors.h"
#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include "../elevio.h"
#include "../con_load.h"


void openDoors(void) {
    elevio_doorOpenLamp(1); // må ha et tidspunkt der dette skrur seg av?
    printf("Door has opened at floor %d\n", elevio_floorSensor());
    obstrucitonStop(); 
    stopButton();

    sleep(3);
    elevio_doorOpenLamp(0);

}

