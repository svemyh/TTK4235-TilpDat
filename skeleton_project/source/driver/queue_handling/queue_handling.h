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

int queueMatrix[4][3] = {
  {0,0,0},
  {0,0,0},
  {0,0,0}
};

int checkQueueAbove(int floor);
int checkQueueBelow(int floor);
void makeFloorRequest(int floor);
void makeButtonRequest(int floor);
int checkQueue(void);
void clearQueue(void);
void clearFloor(int floor);

