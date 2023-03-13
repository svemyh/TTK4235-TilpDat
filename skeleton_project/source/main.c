#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include "driver/elevio.h"
#include "driver/obstructionAndStop/obstructionAndStop.h"

//#define N_FLOORS 4

//typedef enum { 
//    DIRN_DOWN   = -1,
//    DIRN_STOP   = 0,
//    DIRN_UP     = 1
//} MotorDirection;


//#define N_BUTTONS 3

//typedef enum { 
//    BUTTON_HALL_UP      = 0,
//    BUTTON_HALL_DOWN    = 1,
//    BUTTON_CAB          = 2:
//} ButtonType;


//void elevio_init(void);

//void elevio_motorDirection(MotorDirection dirn);
//void elevio_buttonLamp(int floor, ButtonType button, int value);
//void elevio_floorIndicator(int floor);
//void elevio_doorOpenLamp(int value);
//void elevio_stopLamp(int value);

//int elevio_callButton(int floor, ButtonType button);
//int elevio_floorSensor(void);
//int elevio_stopButton(void);
//int elevio_obstruction(void);

type queueMatrix [4][3] = {
    {0,0,0}  // fourth floor
    {0,0,0}  // third floor
    {0,0,0}  // second floor
    {0,0,0}  // first floor
}

void openDoors() {
    elevio_doorOpenLamp(true); // må ha et tidspunkt der dette skrur seg av?
    printf("Door has opened at floor %d\n", elevio_floorSensor());
    while (elevio_obstruction()) { // stopper programmet mens obstruction = true og skrur på stop lamp

        obstrucitonStop();
    } 

    while (elevio_stopButton()) {
        elevio_stopButton();
    }
    sleep(3);
    elevio_doorOpenLamp(false);

}

queueMatrix[elevio_floorSensor()-1][2] = 1; //endrer cab til 1 slik at heisen skjønner at den skal stoppe ved den cabben

switch (elevio_callButton(int floor, 0)) { //bruker dette for å sjekke bevegelse ved floorknapp 
    case 4:
        
        break;
    case 3:

        break;
switch (floorButtonPressed()) { //bruker dette for å endre til hvilken liste i queueMatrix vi jobber med 
    case 4:
        queueMatrix[elevio_floorSensor()-1][]
        break;
    case 3:

        break;
    case 2:
        {

        }
        break;
    case 1:
        {
 i
        }
        break;
}

    case 2:
        {

        }
        break;
    case 1:
        {

        }
        break;
}



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

        else if (BUTTON_HALL_UP && 0 < sum) // moving up
                {
                    while (floor_request (UDEFINERT) () != elevio_floorSensor()) { //dette er jo for når man trykker etasje?
                        elevio_motorDirection(DIRN_UP);
                    }
                    openDoors();
                }

        else if (BUTTON_HALL_DOWN && 0 < sum) // moving down       
                {
                    while (elevio_floorIndicator != elevio_floorSensor) {
                        elevio_motorDirection(DIRN_DOWN);
                    }
                    openDoors();
                }

        else {
            printf("Out of Bounds\n");
        }

        }

    }
}


typedef enum {
    IDLE = 0,
    STOPBUTTON = -2,
    MOVING_UP = 1,
    MOVING_DOWN =-1
} elevatorState;

elevio_callButton(f, b)

int main(){
    // init 
    elevio_init();
    elevio_floorIndicator(0);
    elevio_stopLamp(0);
    elevio_doorOpenLamp(0);
    
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");


    while(1){
        int floor = elevio_floorSensor();
        printf("floor: %d \n",floor);

        //if(floor == 0){
        //    elevio_motorDirection(DIRN_UP);
        //}

        //if(floor == N_FLOORS-1){
        //    elevio_motorDirection(DIRN_DOWN);
        //}
        


        for(int f = 0; f < N_FLOORS; f++){ //skrur floor lamps på og av?
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);
                elevio_buttonLamp(f, b, btnPressed);
            }
        }

    }
    return 0;
}
