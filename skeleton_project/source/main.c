/**
 * @file
 * @brief The main file for elevator
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include "driver/elevio.h"
#include "driver/obstructionAndStop/obstructionAndStop.h"
#include "driver/queue_handling/queue_handling.h"
#include "driver/openDoors/openDoors.h"
#include "driver/elevatorState/elevatorState.h"


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

int main(){
    // init 
    elevio_init();
    elevatorState state = INIT;

    elevio_floorIndicator(0);
    elevio_stopLamp(0);
    elevio_doorOpenLamp(0);
    
    printf("=== Elevator Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");


    while(1){
        int currentFloor = elevio_floorSensor();
        printf("floor: %d \n",currentFloor);

        //if(floor == 0){
        //    elevio_motorDirection(DIRN_UP);
        //}

        //if(floor == N_FLOORS-1){
        //    elevio_motorDirection(DIRN_DOWN);
        //}
        


        for(int f = 0; f < N_FLOORS; f++){ //skrur floor lamps på og av avhengig av hvilken etasje heisen befinner seg i
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);
                elevio_buttonLamp(f, b, btnPressed);
            }
        }

        currentState(currentFloor, &state);
        sleep(3);

    }
    return 0;
}
