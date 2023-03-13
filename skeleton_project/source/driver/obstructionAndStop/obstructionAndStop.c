#include "obstructionAndStop.h"

void obstructionStop() {
            if(elevio_obstruction()){
                elevio_stopLamp(1);
            }
            else {
                elevio_stopLamp(0);
            }
        }

void stopButton() {
            if(elevio_stopButton()){
                elevio_motorDirection(DIRN_STOP);
                elevio_stopLamp(1);
                if(floor != -1){
                    elevio_doorOpenLamp(1);
                }
                while(elevio_stopButton) {};
                nanosleep(&(struct timespecvoid){0, 20*1000*1000}, NULL); //check seconds = 3
                elevator_state.stop_button_pressed = false;
                break;
            }
        }


