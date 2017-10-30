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
int wheelRadius = 47;
int cartWidth=270;
WheelMotor leftWheel= WheelMotor( &PORTF, &DDRF, &OCR5A);
WheelMotor rightWheel= WheelMotor( &PORTK, &DDRK, &OCR4A);
Cart cart= Cart(leftWheel,rightWheel,wheelRadius,cartWidth);
void setup() {
Serial.begin(9600);
setupTimmerForInterrupts();
}

void loop() {
	Serial.println("moving fwd");
	leftWheel.setStepSpeed(30);
	leftWheel.start();
	rightWheel.setStepSpeed(30);
	rightWheel.start();
	//cart.moveForward(3.14*47*4);
	delay(5000);
	Serial.println("turning right");
	leftWheel.stop();
	//cart.rotateRight(90);
	delay(2000);
}

void setupTimmerForInterrupts() {
  // initialize timer1 interupt at every 1000micro sec or 1 milli sec
  //set timer1 interrupt at 1000Hz
  cli();//stop interrupts

  TCCR4A = 0;// set entire TCCR1A register to 0
  TCCR4B = 0;// same for TCCR1B
  TCNT4  = 0;//initialize counter value to 0
  // set compare match register for 1000hz increments
  // calculation for 1024 prescalar 15.625-1
  // @ 256 62.5-1
  //@64 250-1
  OCR4A = (((16000 / 8) * 10) - 1);//For 10 millisec and prescalar 8

  // turn on CTC mode
  TCCR4B |= (1 << WGM42);
  // Set CS10 and CS11 bits for 1 prescaler
  TCCR4B |= (1 << CS41); //Prescalar = 8
  // enable timer compare interrupt
  TIMSK4 |= (1 << OCIE4A);

  // TIMER 5

  TCCR5A = 0;// set entire TCCR1A register to 0
  TCCR5B = 0;// same for TCCR1B
  TCNT5  = 0;//initialize counter value to 0
  // set compare match register for 1000hz increments
  // calculation for 1024 prescalar 15.625-1
  // @ 256 62.5-1
  //@64 250-1
  OCR5A = (((16000 / 8) * 10) - 1);//For 10 millisec and prescalar 8

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
