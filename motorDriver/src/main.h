/*
 * main.h
 *
 *  Created on: Oct 30, 2017
 *      Author: amitp
 */
#ifndef UNIT_TEST
#ifndef SRC_MAIN_H_
#define SRC_MAIN_H_
#include <Arduino.h>
void setupTimmerForInterrupts();
int getMinIndex(int array[]);
int getMaxIndex(int array[]);
void followLine();
int followPath();
boolean moveOneBlockForward();
boolean moveToNextMarker();
int getOnPath();
boolean correctInclination();
boolean moveToNextMarker();
boolean turnLeft();
boolean turnRight();
boolean turnReverse();
#endif /* SRC_MAIN_H_ */
#endif
