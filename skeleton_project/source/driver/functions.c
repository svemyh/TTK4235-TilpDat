#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include "driver/elevio.h"
#include <stdbool.h>



// CLASS-DIAGRAM - Elevator

/**
* @file
* @brief Variable that is to be set to 1 when stop-button is pressed. (May be redundant)
*/
bool stop_button_pressed = 0;

/**
* @brief Variable that is to be set to 1 when elevator is precieving a obstruction. (May be redundant)
*/
bool obstruction_switch = 0;






// CLASS-DIAGRAM - Lighting_enviroment

/**
* @brief A vector corresponding to the floor-lights on the right-hand side, on the top of the "Etasjepanel"-box
*/
bool floor_lights[4] = {0,0,0,0};


/**
* @brief A vector corresponding to the white-green lights labelled "ned" on the left-hand side, on the top of the "Etasjepanel"-box.
*/
bool down_button_lights[3] = {0,0,0};


/**
* @brief A vector corresponding to the yellow-red lights labelled "opp" in the middle, on the top of the "Etasjepanel"-box.
*/
bool up_button_lights[3] = {0,0,0};


/**
* @brief A vector corresponding to the circular lights labelled bottom side on the bottom of "Heispanel".
*/
bool floors_requested_lights[4] = {0,0,0,0};


/**
* @brief Variable to enable when the door of the elevator is open.
*/
bool door_is_open_light = 0;


/**
* @brief Variable that is to be set to 1 when stop-button is pressed. Signifies that the red stop-button-lamp on "Heispanel" is enabled. (May be redundant)
*/
bool stop_light = 0;




// CLASS-DIAGRAM - Requests

/**
* @brief 
*/

bool g_floor_requests[4][3] = {{0,0,0},
			       {0,0,0},
			       {0,0,0},
			       {0,0,0}};
			     




// CLASS-DIAGRAM - Elevator_logic

/**
* @brief (This variable may be redundant)
*/
int current_floor = -1;

/**
* @brief (This variable may be redundant)
*/
int next_floor = -1;

/**
* @brief (This variable may be redundant)
*/
int prev_floor = -1;


/**
* @brief Boolean. (This variable may be redundant)
*/
bool is_idle = 1;

/**
* @brief Boolean. (This variable may be redundant)
*/
bool door_is_open = 0;





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
	g_floor_requests = {{0,0,0},
			    {0,0,0},
			    {0,0,0},
			    {0,0,0}};
			
		
			
// Idea: Move 2 units (not floors, but specified distance) up, 1 down adn then start procedure below:
	
	
	if (current_floor = -1 & (elevio_obstruction == false)){
		elevio_motorDirection(DIRN_DOWN);
	} 
}

void flow_control(void){
	
}

void testlamps




/// ref. STATE-DIAGRAM

enum state {
	INIT,
	IDLE,
	MOVING_UP,
	MOVING_DOWN,
	STOP_BUTTON,
};



