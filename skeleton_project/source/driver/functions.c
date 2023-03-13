#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include "elevio.h"
#include <stdbool.h>




// CLASS-DIAGRAM - Elevator_logic



// Assuming current_floor ∈ {0,1,2,3}
bool thereIsAnOrderFromFloorsAbove(int current_floor,  int g_floor_requests[4][3]){
	
	for (int i = current_floor; i < 4; ++i)
	  {
	      printf("Hello there!");
	      if ((g_floor_requests[i][0]==1) ||
	          (g_floor_requests[i][1]==1) ||
	          (g_floor_requests[i][2]==1)){
	      	return 1;  //boolean
	      }
	  }
	
	return 0;  //boolean
};


// Assuming current_floor ∈ {0,1,2,3}
bool thereIsAnUpwardgoingOrderFromFloorsAbove(int current_floor,  int g_floor_requests[4][3]){
	
	for (int i = current_floor; i < 4; ++i)
	  {
	      printf("Hello there!");
	      if ((g_floor_requests[i][1]==1) ||
	          (g_floor_requests[i][2]==1)){
	      	return true;  //boolean
	      }
	  }
	
	return false;  //boolean
};



void startup(){
	//g_floor_requests = {{0,0,0},
	//		    {0,0,0},
	//		    {0,0,0},
	//		    {0,0,0}};
			
		
			
// Idea: Move 2 units (not floors, but specified distance) up, 1 down adn then start procedure below:
	
	int a = 2;
	//if (current_floor = -1 & (elevio_obstruction == false)){
//		elevio_motorDirection(DIRN_DOWN);
//	} 
}

void flow_control(void){
	int a = 2;
	printf("hello there!\n");
}

void helloWorld(void){
	printf("Hello there!\n");
}


void flashLights(void){

	elevio_motorDirection(DIRN_STOP);
	
	elevio_buttonLamp(1, 1, 1);
	elevio_buttonLamp(1, 2, 1);
	elevio_buttonLamp(1, 3, 1);
}










/// ref. STATE-DIAGRAM

enum state {
	INIT,
	IDLE,
	MOVING_UP,
	MOVING_DOWN,
	STOP_BUTTON,
};



