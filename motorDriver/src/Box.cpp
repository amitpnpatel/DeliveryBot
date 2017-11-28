/*
* Box.cpp
*
*  Created on: Nov 6, 2017
*      Author: amitp
*/
#include "Box.h"
Box::Box(int centre,int inclination,boolean state,boolean onMarker){
	this->centre=centre;
	this->inclination=inclination;
	this->state=state;
	this->onMarker=onMarker;
	this->updateState=false;
}
void Box::setCentre(int centre){
	this->centre=centre;
}
void Box::setInclination(int inclination){
	this->inclination=inclination;
}
int Box::getCentre(){
	checkSensor();
	return centre;
}
int Box::getInclination(){
	checkSensor();
	return inclination;
}
void Box::setState(boolean state){
	checkSensor();
	this->state=state;
}
boolean Box::getState(){
	checkSensor();
	return state;
}
void Box::setOnMarker(boolean mark){
	checkSensor();
	this->onMarker=mark;
}
boolean Box::isOnMarker(){
	checkSensor();
	return onMarker;
}
void Box::setParams(boolean state,int centre,int inclination,boolean onMark){
	setState(state);
	setCentre(centre);
	setInclination(inclination);
	setOnMarker(onMark);
	this->updateState=true;
}
boolean Box::waitTillNextUpdate(){
	this->updateState=false;
	int counter=0;
	while(!updateState){
		if(counter>100){
			return false;
		}
		counter++;
		delay(10);
		checkSensor();
	}
	return true;
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
void Box::checkSensor(){
	while (Serial1.available()) {
		char inChar = readNextCharacterFromSerial1();
		if (inChar == 'S') {
			inChar = readNextCharacterFromSerial1();
			if (inChar == 'L') {
				inChar = readNextCharacterFromSerial1();
				if (inChar == 'C') {
					boolean state = readNextByteFromSerial1();
					int centre = readNextByteFromSerial1();
					int inclination = readNextByteFromSerial1();
					boolean onMark = readNextByteFromSerial1();
					inChar = readNextCharacterFromSerial1();
					if (inChar == 'E') {
						setParams(state,centre,inclination - 50,onMark);
					}
				}
			}
		}
	}
}
