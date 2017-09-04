/*
 * main.cpp
 *
 *  Created on: Jun 23, 2017
 *      Author: amitp
 */

#include <Arduino.h>
#include <WheelMotor.h>
#include <Cart.h>
int wheelRadius = 47;
int cartWidth=270;
WheelMotor leftWheel= WheelMotor( &PORTB, &DDRB);
WheelMotor rightWheel= WheelMotor( &PORTC, &DDRC);
Cart cart= Cart(leftWheel,rightWheel,wheelRadius,cartWidth);
void setup() {
Serial.begin(9600);
}

void loop() {
	Serial.println("moving fwd");
	cart.moveForward(3.14*47*4);
	delay(2000);
	Serial.println("turning right");
	cart.rotateRight(90);
	delay(2000);
}
