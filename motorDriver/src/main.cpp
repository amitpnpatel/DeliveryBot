/*
* main.cpp
*
*  Created on: Jun 23, 2017
*      Author: amitp
*/

#include <Arduino.h>
#include <WheelMotor.h>
#include <Cart.h>
#include <main.h>
#include <Box.h>
int wheelRadius = 47;
int cartWidth = 270;
Box path(50, 0, true);
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
	path.checkSencor();
}
boolean correctInclination(){
	int halfStepTime=20;
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
	if ((path.getCentre() < 70) && (path.getCentre() > 30) && (path.getInclination() < 20) && (path.getInclination() > -20)) {
		if((path.getInclination() < -5) && (path.getInclination() > 5)){
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
	int halfStepTime=20;
	while (path.getCentre() > 55 || path.getCentre() < 45) {
		if (path.getCentre() > 55) {
			leftWheel.setForwordDirection();
			rightWheel.setForwordDirection();
			cart.powerUpWheels();
			for (int turnstep = 0; turnstep < 4; turnstep++) {
				leftWheel.moveStep();
				delay(halfStepTime);
			}
			correctInclination();
		} else if (path.getCentre() < 45) {
			rightWheel.setForwordDirection();
			cart.powerUpWheels();
			for (int turnstep = 0; turnstep < 4; turnstep++) {
				rightWheel.moveStep();
				delay(halfStepTime);
			}
			correctInclination();
		}
		path.waitTillNextUpdate();
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
		if (moveOneBlockForward()) {
			Serial.println("moved 1 block");
		} else {
			Serial.println("lost path");
		}
		delay(1000);
	}
}
boolean moveOneBlockForward() {
	for (int step = 0; step < 800; step++) {
		int stepMoved=followPath();
		if (stepMoved>1) {
			step+=(stepMoved-1);
		}
		delay(15);
	}
	cart.powerDownWheels();
	return true;
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
