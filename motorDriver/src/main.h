/*
 * main.h
 *
 *  Created on: Oct 30, 2017
 *      Author: amitp
 */

#ifndef SRC_MAIN_H_
#define SRC_MAIN_H_
#include <Arduino.h>
void setupTimmerForInterrupts();
int getMinIndex(int array[]);
int getMaxIndex(int array[]);
void followLine();
int followPath();
boolean moveOneBlockForward();
int getOnPath();
boolean correctInclination();
#endif /* SRC_MAIN_H_ */
