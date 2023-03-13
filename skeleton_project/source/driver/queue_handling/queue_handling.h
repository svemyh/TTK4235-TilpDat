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

void clearQueue(void);

