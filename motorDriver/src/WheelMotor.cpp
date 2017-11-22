/*
 * WheelMotor.cpp
 *
 *  Created on: Jun 26, 2017
 *      Author: amitp
 */
#include <Arduino.h>
#include <WheelMotor.h>
WheelMotor::WheelMotor(){
	motorPort=&PORTB;
	DDRB|=0b11111111;
	timeCompareRegister=0;
	motorState=false;
}
WheelMotor::WheelMotor(volatile uint8_t *_motorPort, volatile uint8_t *portAddressDDR,
		 volatile uint16_t *_timeCompareRegister){
	motorPort=_motorPort;
	timeCompareRegister=_timeCompareRegister;
	*portAddressDDR |= 0b11111111 ;
	powerDown();
}
boolean WheelMotor::stop(){
	motorState = false;
	powerDown();
	return true;
}
boolean WheelMotor::start(){
	motorState = true;
    powerUp();
    return true;
}
void WheelMotor::moveStep(){
	*motorPort ^= 0b00000001;
	currentStepNumber++;
}
void WheelMotor::reset(){
	 *motorPort &= 0b11111011;
	 delayMicroseconds(5);
	 *motorPort |= 0b00000100;
}
void WheelMotor::sleep(){
	*motorPort &= 0b11110111;
}
void WheelMotor::wakeUp(){
	*motorPort |= 0b00001000;
}
void WheelMotor::powerUp(){
	*motorPort &= 0b11101111;
}
void WheelMotor::powerDown(){
	*motorPort |= 0b00010000;
}
void WheelMotor::setForwordDirection(){
	*motorPort |= 0b00000010;
}
void WheelMotor::setReverseDirection(){
	*motorPort &= 0b11111101;
}
void WheelMotor::tick(){

	if(motorState){
		moveStep();
	}
}
void WheelMotor::setStepCount(int step){
	currentStepNumber=step;
}
int WheelMotor::getStepCount(){
	return currentStepNumber;
}
void WheelMotor::setStepSpeed(int stepTime){
	*timeCompareRegister=stepTime*2000;
}
