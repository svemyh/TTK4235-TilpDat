/**
 * @file
 * @brief The library for queue handling
 */
#pragma once

#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <assert.h>
#include <stdlib.h>

#include "../elevio.h"
#include "../con_load.h"
#include "../openDoors/openDoors.h"

extern int queueMatrix[N_FLOORS][N_BUTTONS];

int checkQueueAbove(int floor);
int checkQueueBelow(int floor);
void makeFloorRequest(int floor);
void makeButtonRequest(int floor);
int checkQueue(void);
void clearQueue(void);
void clearFloor(int floor);

