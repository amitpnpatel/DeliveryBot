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
void followLine() {
	int sensorValue[5];
	sensorValue[0] = analogRead(A0);
	sensorValue[1] = analogRead(A1);
	sensorValue[2] = analogRead(A2);
	sensorValue[3] = analogRead(A3);
	sensorValue[4] = analogRead(A4);
	//int lindIndex = getMinIndex(sensorValue);
	int lindIndex = getMaxIndex(sensorValue);
	if (isSensorValid(sensorValue)) {
		Serial.print("min index");
		Serial.println(lindIndex);
		leftWheel.setForwordDirection();
		rightWheel.setForwordDirection();
		cart.powerUpWheels();
		if (lindIndex == 2) {
			leftWheel.moveStep();
			rightWheel.moveStep();
		} else if (lindIndex > 2) {
			leftWheel.moveStep();
		} else if (lindIndex < 2) {
			rightWheel.moveStep();
		}
	} else {
		cart.powerDownWheels();
	}
}
char readNextCharacterFromSerial1() {
	while (Serial1.available() == 0) {
	}
	return (char) Serial1.read();
}
byte readNextByteFromSerial1() {
	while (Serial1.available() == 0) {
	}
	return Serial1.read();
}
void checkSensor() {
	while (Serial1.available()) {
		char inChar = readNextCharacterFromSerial1();
		if (inChar == 'S') {
			inChar = readNextCharacterFromSerial1();
			if (inChar == 'L') {
				inChar = readNextCharacterFromSerial1();
				if (inChar == 'C') {
					boolean state = readNextByteFromSerial1();
					int centre = readNextByteFromSerial1();
					int inclination = readNextByteFromSerial1() - 50;
					inChar = readNextCharacterFromSerial1();
					if (inChar == 'E') {
						path.setState(state);
						path.setCentre(centre);
						path.setInclination(inclination);
					}
				}

			}
		} else if (inChar == 'G') {

		}
	}
}
void followpath() {
	if ((path.getCentre() < 70) && (path.getCentre() > 30)
			&& (path.getInclination() < 20) && (path.getInclination() > -20)) {
		leftWheel.setForwordDirection();
		rightWheel.setForwordDirection();
		cart.powerUpWheels();
		leftWheel.moveStep();
		rightWheel.moveStep();
	} else {
		cart.powerDownWheels();
	}
}
void loop() {
//	Serial.println("moving fwd");
//	leftWheel.setStepSpeed(30);
//	leftWheel.start();
//	rightWheel.setStepSpeed(30);
//	rightWheel.start();
//	//cart.moveForward(3.14*47*4);
//	delay(5000);
//	Serial.println("turning right");
//	leftWheel.stop();
//	//cart.rotateRight(90);
	checkSensor();
	followpath();
	delay(500);
}

int getMinIndex(int array[]) {
	int result = 0;
	for (int index = 1; index < 5; index++) {
		if (array[result] > array[index]) {
			result = index;
		}
	}
	return result;
}
int getMaxIndex(int array[]) {
	int result = 0;
	for (int index = 1; index < 5; index++) {
		if (array[result] < array[index]) {
			result = index;
		}
	}
	return result;
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
