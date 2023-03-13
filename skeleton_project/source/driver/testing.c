
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>

#include "testing.h"
#include "elevio.h"


void helloWorld(void){
	printf("sss");
}



void flashLights(void){

	elevio_motorDirection(DIRN_STOP);
	
	elevio_buttonLamp(1, 1, 1);
	elevio_buttonLamp(1, 2, 1);
	elevio_buttonLamp(1, 3, 1);
	return 0;
}






