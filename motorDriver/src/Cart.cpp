/*
 * Cart.cpp
 *
 *  Created on: Jun 26, 2017
 *      Author: amitp
 */
#include <Arduino.h>
#include <Cart.h>
#include <WheelMotor.h>

Cart::Cart(WheelMotor left, WheelMotor right, int radius, int mountingWidth) {
	leftWheel = left;
	rightWheel = right;
	wheelRadius = radius;
	width = mountingWidth;
}
boolean Cart::moveForward(long distance) {
	Serial.println(distance);
	long step = ((distance * 200) / (3.143 * wheelRadius));
	leftWheel.setForwordDirection();
	rightWheel.setForwordDirection();
	powerUpWheels();
	int stepTime = 10000;
		for (long stepcount = 0; stepcount < step; stepcount++) {
			leftWheel.moveStep();
			rightWheel.moveStep();
			delayMicroseconds(stepTime);
			if (stepTime > 5000) {
				stepTime -= 100;
			}
		}
	powerDownWheels();
	return true;
}
boolean Cart::moveReverse(long distance) {
	long step = ((distance * 200) / (3.143 * wheelRadius));
	leftWheel.setReverseDirection();
	rightWheel.setReverseDirection();
	powerUpWheels();
	int stepTime = 10000;
		for (long stepcount = 0; stepcount < step; stepcount++) {
			leftWheel.moveStep();
			rightWheel.moveStep();
			delayMicroseconds(stepTime);
			if (stepTime > 5000) {
				stepTime -= 100;
			}
		}
	powerDownWheels();
	return true;
}
boolean Cart::rotateRight(long angle) {
	long step = (angle * 5 * width) / (9 * wheelRadius);
	leftWheel.setForwordDirection();
	rightWheel.setReverseDirection();
	powerUpWheels();
	int stepTime = 10000;
	for (long stepcount = 0; stepcount < step; stepcount++) {
		leftWheel.moveStep();
		rightWheel.moveStep();
		delayMicroseconds(stepTime);
	}
	powerDownWheels();
	return true;
}
boolean Cart::rotateLeft(long angle) {
	long step = (angle * 5 * width) / (9 * wheelRadius);
	rightWheel.setForwordDirection();
	leftWheel.setReverseDirection();
	powerUpWheels();
	int stepTime = 10000;
	for (long stepcount = 0; stepcount < step; stepcount++) {
		leftWheel.moveStep();
		rightWheel.moveStep();
		delayMicroseconds(stepTime);
	}
	powerDownWheels();
	return true;
}
boolean Cart::powerUpWheels() {
	leftWheel.powerUp();
	rightWheel.powerUp();
	return true;
}
boolean Cart::powerDownWheels() {
	leftWheel.powerDown();
	rightWheel.powerDown();
	return true;
}
