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

int btnPressed = elevio_callButton(f, 0));
switch(btnPressed) { //bruker dette for å sjekke bevegelse ved floorknapp 
    case 4:

        queueMatrix[elevio_callButton(f, b)-1][2] = 1; 
        break;
    case 3:
        queueMatrix[elevio_callButton(f, b)-1][2] = 1; 
    case 2:
        queueMatrix[elevio_callButton(f, b)-1][2] = 1; 
        break;
    case 1:
        queueMatrix[elevio_callButton(f, b)-1][2] = 1; 
        break;
}



void floorPressed(void) {
    queueMatrix[elevio_callButton(f, b)-1][2] = 1; // sets a true to floor cab(a number to tell the elevator to stop)
    for (int i = 0; i < 4; i++) { //move this in while loop
    
        for (int j = 0; j < 3, j++) {
    
            int sum;
            sum += queueMatrix[i][3];
        
            if (sum == 0): //idle 
                    {
                        elevio_motorDirection(DIRN_STOP);
                        elevio_doorOpenLamp(true);
                         
                    }
            else if (elevio_stopButton())  // stop button initiated. Lets move this outside the for loop? Or have an interrupt
                    {
                        stopButton();
                    }

            else if (elevio_obstruction()) // obstruction 
                    {
                        obstructionStop();
                    }

            else if (BUTTON_HALL_UP && 0 < sum) { //moving up
                while (elevio_callButton(f, b) != elevio_floorSensor()) { //dette er jo for når man trykker etasje?
                    elevio_motorDirection(DIRN_UP);
                    if (elevio_floorSensor() = elevio_callButton(f, b)) { //skrur av cab 
                        queueMatrix[elevio_floorSensor()-1][2] = 0;
                        break;
                    }
                }
                openDoors();
            }
    
            else if (BUTTON_HALL_DOWN && 0 < sum) // moving down       
            {
                while (elevio_callButton(f, b) != elevio_floorSensor) {
                    elevio_motorDirection(DIRN_DOWN);
                    if (elevio_floorSensor() = elevio_callButton(f, b)) { //skrur av cab 
                        queueMatrix[elevio_floorSensor()-1][2] = 0;
                        break;
                    }
                }
                openDoors();
            }

            else {
                printf("Out of Bounds\n");
            }

            }
    
        }
    }
} 

void clearQueue(void) {
    elevio_doorOpenLamp(0);
    for(int f = 0; f < N_FLOORS; f++){ //skrur floor lamps av
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


