/**
 * @file
 * @brief The library of obstruction and stop cases
 */
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include "../../driver/elevio.h" 

void obstructionStop();
void stopButton(int currentFloor);
