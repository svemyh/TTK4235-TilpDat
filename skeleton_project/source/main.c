#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include "driver/elevio.h"

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
#define queue_size 100

//queue handling system
List<List<string>> queue_list = new List<List<bool>>();
queue_list.Add(new List<bool> {0,0,0}); //opp, ned, cab. cab beskriver utløser open doors dersom current list == current floor 
queue_list.Add(new List<bool> {0,0,0});
queue_list.Add(new List<bool> {0,0,0});
queue_list.Add(new List<bool> {0,0,0});

int main(){
    elevio_init();
    elevio_floorIndicator(0);
    elevio_stopLamp(0);
    elevio_buttonLamp(0);
    elevio_doorOpenLamp(0);

    // queue handling system
    
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    elevio_motorDirection(DIRN_UP);

    while(1){
        int floor = elevio_floorSensor();
        printf("floor: %d \n",floor);

        if(floor == 0){
            elevio_motorDirection(DIRN_UP);
        }

        if(floor == N_FLOORS-1){
            elevio_motorDirection(DIRN_DOWN);
        }


        for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);
                elevio_buttonLamp(f, b, btnPressed);
            }
        }

        //STOP
	obstructionStop();
	stopButton();
    }

    sleep(3); // wait 3 sec
    return 0;
}
