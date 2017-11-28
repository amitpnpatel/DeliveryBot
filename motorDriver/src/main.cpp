/*
* main.cpp
*
*  Created on: Jun 23, 2017
*      Author: amitp
*/
#ifndef UNIT_TEST
#include <Arduino.h>
#include <WheelMotor.h>
#include <Cart.h>
#include <main.h>
#include <Box.h>
int wheelRadius = 47;
int cartWidth = 270;
Box path(50, 0, true,false);
WheelMotor leftWheel = WheelMotor(&PORTA, &DDRA, &OCR5A);
WheelMotor rightWheel = WheelMotor(&PORTK, &DDRK, &OCR4A);
Cart cart = Cart(leftWheel, rightWheel, wheelRadius, cartWidth);
void setup() {
	Serial.begin(9600);
	Serial1.begin(9600);
	setupTimmerForInterrupts();
}
boolean isSensorValid(int sensorValue[]) {
	return true;
}
void checkSensors() {
	path.checkSensor();
}
boolean correctInclination(){
	int halfStepTime=15;
	while (path.getInclination() > 4 || path.getInclination() < -4) {
		if (path.getInclination() > 4) {
			leftWheel.setForwordDirection();
			cart.powerUpWheels();
			leftWheel.moveStep();
		} else if (path.getInclination()< -4) {
			rightWheel.setForwordDirection();
			cart.powerUpWheels();
			rightWheel.moveStep();
		}
		delay(halfStepTime);
	}
	cart.powerDownWheels();
	return true;
}

int followPath() {
	if ((path.getCentre() < 60) && (path.getCentre() > 40) && (path.getInclination() < 10) && (path.getInclination() > -10)) {
		if((path.getInclination() < -4) && (path.getInclination() > 4)){
			correctInclination();
		}
		leftWheel.setForwordDirection();
		rightWheel.setForwordDirection();
		cart.powerUpWheels();
		leftWheel.moveStep();
		rightWheel.moveStep();
	} else {
		return getOnPath();
	}
	return 1;
}

int getOnPath() {
	int result=0;
	correctInclination();
	int halfStepTime=15;
	while (path.getCentre() > 55 || path.getCentre() < 45) {
		if (path.getCentre() > 55) {
			leftWheel.setForwordDirection();
			rightWheel.setForwordDirection();
			cart.powerUpWheels();
			int correctionStep=(path.getCentre()-50)/2;
			if(correctionStep<8){
				correctionStep=8;
			}
			for (int turnstep = 0; turnstep < 8; turnstep++) {
				leftWheel.moveStep();
				delay(halfStepTime);
			}
			correctInclination();
		} else if (path.getCentre() < 45) {
			rightWheel.setForwordDirection();
			cart.powerUpWheels();
			int correctionStep=(50-path.getCentre())/2;
			if(correctionStep<8){
				correctionStep=8;
			}
			for (int turnstep = 0; turnstep < 8; turnstep++) {
				rightWheel.moveStep();
				delay(halfStepTime);
			}
			correctInclination();
		}
		path.waitTillNextUpdate();
		result+=2;
	}
	cart.powerDownWheels();
	return result;
}
void loop() {
	delay(5000);
	Serial.println("moving fwd");
	for(int index=0;index<6;index++){
		if (moveToNextMarker()) {
			if(turnReverse()){
				moveToNextMarker();
			}
			Serial.println("moved 1 marker");
		} else {
			Serial.println("lost path");
		}
		delay(10000);
	}
}
boolean turnLeft(){
	for (int step = 0; step < 1200; step++) {
		if(step>400){
			if(path.getState()){
				if((path.getInclination() > -8) && (path.getInclination() < 8)){
					getOnPath();
					cart.powerDownWheels();
					return true;
				}
			}
		}
		leftWheel.setForwordDirection();
		rightWheel.setForwordDirection();
		cart.powerUpWheels();
		rightWheel.moveStep();
		delay(15);
	}
	cart.powerDownWheels();
	return false;
}
boolean turnReverse(){
	for (int step = 0; step < 1000; step++) {
		if(step>600){
			if(path.getState()){
				if((path.getInclination() > -8) && (path.getInclination() < 8)){
					getOnPath();
					cart.powerDownWheels();
					return true;
				}
			}
		}
		leftWheel.setForwordDirection();
		rightWheel.setReverseDirection();
		cart.powerUpWheels();
		leftWheel.moveStep();
		rightWheel.moveStep();
		delay(15);
	}
	cart.powerDownWheels();
	return false;
}
boolean turnRight(){
	for (int step = 0; step < 1200; step++) {
		if(step>400){
			if(path.getState()){
				if((path.getInclination() > -8) && (path.getInclination() < 8)){
					getOnPath();
					cart.powerDownWheels();
					return true;
				}
			}
		}
		leftWheel.setForwordDirection();
		rightWheel.setForwordDirection();
		cart.powerUpWheels();
		leftWheel.moveStep();
		delay(15);
	}
	cart.powerDownWheels();
	return false;
}
boolean moveOneBlockForward() {
	for (int step = 0; step < 800; step++) {
		if(!path.getState()){
			continue;
		}
		int stepMoved=followPath();
		if (stepMoved>1) {
			step+=(stepMoved-1);
		}
		delay(15);
	}
	cart.powerDownWheels();
	return true;
}
boolean moveToNextMarker(){
	boolean oldMarkerState=true;
	getOnPath();
	for (int step = 0; step < 2000; step++) {
		if(!path.getState()){
			path.waitTillNextUpdate();
			if(!path.getState()){
				cart.powerDownWheels();
				return false;
			}
		}
		if(path.isOnMarker()){
			if(step>50 && (!oldMarkerState)){
				correctInclination();
				cart.powerDownWheels();
				return true;
			}
		}else{
			oldMarkerState=false;
		}
		int stepMoved=followPath();
		if (stepMoved>1) {
			step+=(stepMoved-1);
		}
		delay(15);
	}
	correctInclination();
	cart.powerDownWheels();
	return false;
}
void setupTimmerForInterrupts() {
	// initialize timer1 interupt at every 1000micro sec or 1 milli sec
	//set timer1 interrupt at 1000Hz
	cli();
	//stop interrupts

	TCCR4A = 0;  // set entire TCCR1A register to 0
	TCCR4B = 0;  // same for TCCR1B
	TCNT4 = 0;  //initialize counter value to 0
	// set compare match register for 1000hz increments
	// calculation for 1024 prescalar 15.625-1
	// @ 256 62.5-1
	//@64 250-1
	OCR4A = (((16000 / 8) * 10) - 1);  //For 10 millisec and prescalar 8

	// turn on CTC mode
	TCCR4B |= (1 << WGM42);
	// Set CS10 and CS11 bits for 1 prescaler
	TCCR4B |= (1 << CS41); //Prescalar = 8
	// enable timer compare interrupt
	TIMSK4 |= (1 << OCIE4A);

	// TIMER 5

	TCCR5A = 0;  // set entire TCCR1A register to 0
	TCCR5B = 0;  // same for TCCR1B
	TCNT5 = 0;  //initialize counter value to 0
	// set compare match register for 1000hz increments
	// calculation for 1024 prescalar 15.625-1
	// @ 256 62.5-1
	//@64 250-1
	OCR5A = (((16000 / 8) * 10) - 1);  //For 10 millisec and prescalar 8

	// turn on CTC mode
	TCCR5B |= (1 << WGM52);
	// Set CS10 and CS11 bits for 1 prescaler
	TCCR5B |= (1 << CS51); //Prescalar = 8
	// enable timer compare interrupt
	TIMSK5 |= (1 << OCIE5A);

	sei();
}

ISR(TIMER4_COMPA_vect) {
	rightWheel.tick();
}

ISR(TIMER5_COMPA_vect) {
	leftWheel.tick();
}
#endif
